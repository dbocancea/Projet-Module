#include <chrono>
#include <thread>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include "../src/Core/ModuleTypes.hpp"
#include "../src/Core/ModuleRegistry.hpp"



int main() {
    ix::initNetSystem();


    ix::WebSocket webSocket;
    string url = "ws://0.0.0.0:3000/"; // server address 
    webSocket.setUrl(url);

    string strTestUUID = "1acc3893-6a29-486b-96b7-eea902b76504b";
    boost::json::value testUUID = {
        {"UUID", strTestUUID}
    };
    uint128_t UUID = 444425;

    ModuleRegistry modules([&](json::value){
        std::cout << "test" << endl;
    });

    modules.AddModule("CameraModule", 123, 0);

//    cout << boost::json::serialize(modules.GetState());
    boost::json::value instJoin = {
        {"scope", "SYSTEM"},
        {"senderUUID", strTestUUID},
        {"payload", boost::json::object{
            {"command", "INSTANCE_JOIN"},
            {"data", boost::json::object{
                {"instanceUUID", "00000000-0000-0000-0000-000000000000"},
                {"userUUID", strTestUUID}
            }}
        }}
    };
    std::string instJoinStr = boost::json::serialize(instJoin);
    std::cout << instJoinStr << endl;

    std:: string uuidStr = boost::json::serialize(testUUID);
    std::string stateStr = boost::json::serialize(modules.GetState());

    webSocket.setOnMessageCallback([&](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Open) {
            std::cout << "[CONNECTED] Successfully shook hands with Server!" << endl;
            std::cout << "Sent Identification..." << endl;
            webSocket.send(uuidStr);

            cout << "trying to init..." << endl; 
            webSocket.send(instJoinStr); 

            cout << "trying to create camera module..." << endl; 
            webSocket.send(stateStr);
            
         //   webSocket.send(jsonStr);
            //       webSocket.send("{\"command\":\"INSTANCE_JOIN\",\"data\":{\"instanceUUID\":\"00000000-0000-0000-0000-000000000000\",\"userUUID\":\"1acc3893-6a29-486b-96b7-eea902b7650b\"}}");
           // webSocket.send(stateStr);
        } 
        // if (msg->str.find("INSTANCE_LIST") != std::string::npos) {
        //         std::cout << "[SYSTEM] Server is ready! Sending JOIN and STATE commands..." << endl;
                
        // }

        else if (msg->type == ix::WebSocketMessageType::Message) {
            std::cout << "[RECEIVED FROM SERVER] " << msg->str << endl;
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

    std::cout << "Type messages below and press Enter to send (or 'exit' to quit):\n" << endl;
    string userInput;
    while (true) {
        getline(cin, userInput);
        if (userInput == "exit") {
            break;
        }

        if (webSocket.getReadyState() == ix::ReadyState::Open) {
            webSocket.send(userInput);
        } else {
            std::cout << "[SYSTEM] Message not sent. ReadyState isn't open yet..." << endl;
        }
    }

    std::cout << "Stopping WebSocket background loops..." << endl;
    webSocket.stop();
    ix::uninitNetSystem();
    return 0;
}