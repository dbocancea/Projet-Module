#include <chrono>
#include <thread>
//#include <mutex>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include "../src/Core/ModuleTypes.hpp"
#include "../src/Core/ModuleRegistry.hpp"

int main() {
    ix::initNetSystem();
    uuids::random_generator gen;
    ix::WebSocket webSocket;
    string url = "ws://0.0.0.0:8080/"; // server address
    webSocket.setUrl(url);

    uuids::uuid TestUUID = gen();
    string strTestUUID = uuids::to_string(TestUUID);
    boost::json::value testUUID = {
        {"UUID", strTestUUID}
    };

    uuids::uuid UUID = gen();
    uuids::uuid UUID1 = gen();
    bool instanceJoined = false;

    ModuleRegistry modules([&](json::value outData){
        if (webSocket.getReadyState() == ix::ReadyState::Open) {
            boost::json::value wrapped = {
                {"scope", "MODULE"},
                {"senderUUID", strTestUUID},
                {"payload", outData}
            };
            std::string data = boost::json::serialize(wrapped);
            webSocket.send(data);
        }
    });

    boost::json::value instJoin = {
        {"scope", "SYSTEM"},
        {"senderUUID", strTestUUID},
        {"payload", boost::json::object{
            {"command", "INSTANCE_JOIN"},
            {"data", boost::json::object{
                {"instanceUUID", uuids::to_string(uuids::nil_generator()())},
                {"userUUID", strTestUUID}
            }}
        }}
    };
    std::cout << instJoin << endl;
    std::string instJoinStr = boost::json::serialize(instJoin);

    std:: string uuidStr = boost::json::serialize(testUUID);

    webSocket.setOnMessageCallback([&](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Open) {
            std::cout << "[CONNECTED] Successfully shook hands with Server!" << endl;
            std::cout << "Sent Identification..." << endl;
            webSocket.send(uuidStr);
            webSocket.send(instJoinStr); 
            modules.AddModule("CameraModule", UUID, 1);
        }

        else if (msg->type == ix::WebSocketMessageType::Message) {
            std::cout << "[RECEIVED FROM SERVER] " << msg->str << endl;

            boost::json::value incomingData = boost::json::parse(msg->str);
            auto &obj = incomingData.as_object();

            if (!obj.contains("payload") || !obj.contains("scope"))
                return;

            string scope = obj.at("scope").as_string().c_str();
            auto &payload = obj.at("payload").as_object();

                if (scope == "MODULE" && payload.contains("command")) {
                    string command = payload.at("command").as_string().c_str();
                    string moduleUUIDStr = payload.at("moduleUUID").as_string().c_str();
                    uuids::uuid moduleUUID = uuids::string_generator{}(moduleUUIDStr);

                    bool isRegistryTarget = (moduleUUID == uuids::nil_generator()());

                    if (command == "SET_STATE" && isRegistryTarget) {
                        boost::json::value stateData = payload.at("data");
                        modules.SetState(stateData);

                        auto &modulesArr = stateData.as_object().at("modulesData").as_array();
                        bool found = false;
                        for (auto &entry : modulesArr) {
                            string uStr = entry.as_object().at("UUID").as_string().c_str();
                            if (uuids::string_generator{}(uStr) == UUID) { found = true; break; }
                        }
                        std::cout << (found
                            ? "[SYSTEM] Confirmed: server has the module\n"
                            : "[SYSTEM] Server does NOT have the module yet\n");
                    }
                    else if (command == "ADD_MODULE" && isRegistryTarget) {
                        auto &data = payload.at("data").as_object();
                        string addedUUIDStr = data.at("UUID").as_string().c_str();
                        uuids::uuid addedUUID = uuids::string_generator{}(addedUUIDStr);

                        if (addedUUID == UUID) {
                            std::cout << "[SYSTEM] Confirmed: server saved our module ("
                                    << data.at("type").as_string() << ")\n";
                        } else {
                            std::cout << "[SYSTEM] Another client's module was added: "
                                    << addedUUIDStr << "\n";
                        }
                    }
                    else {
                        auto module = modules.GetModule(moduleUUID);
                        if (module) module->input(payload);
                    }
                }
            }
        }
        else if (msg->type == ix::WebSocketMessageType::Close) {
            std::cout << "[DISCONNECTED] Connection closed. Reason: " << msg->closeInfo.reason << endl;
        }
        else if (msg->type == ix::WebSocketMessageType::Error) {
            std::cout << "[ERROR] Connection failure: " << msg->errorInfo.reason << endl;
        }
    });

    std::cout << "Connecting to " << url << "..." << endl;
    webSocket.start();

    std::cout << "Waiting for handshake..." << std::endl;
    int timeoutCheck = 0;
    while (webSocket.getReadyState() != ix::ReadyState::Open) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        timeoutCheck++;

        if (timeoutCheck > 50) {
            std::cerr << "\n[SYSTEM] Connection timed out! Is the server running?" << std::endl;
            webSocket.stop();
            ix::uninitNetSystem();
            return 1;
        }
    }

    std::cout << "\nType 'exit' to quit\n" << endl;
    string userInput;
    while (true) {
        getline(cin, userInput);
        if (userInput == "exit") {
            break;
        }
    }

    std::cout << "Stopping WebSocket background loops..." << endl;
    webSocket.stop();
    ix::uninitNetSystem();
    return 0;
}