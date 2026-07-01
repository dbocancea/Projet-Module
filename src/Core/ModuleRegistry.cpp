#include "ModuleRegistry.hpp"

ModuleRegistry::ModuleRegistry() {}

ModuleRegistry::ModuleRegistry(function<void(json::value)> outputFn) : ModuleCore(0)
{
    this->modules[0] = shared_from_this();

    string cmd1 = "ADD_MODULE";

    string cmd2 = "REMOVE_MODULE";

    this->command.push_back(cmd1);
    this->command.push_back(cmd2);
    this->outputFn = outputFn;
    this->SetOnCommand(cmd1, [this](json::value data)
                       { this->OnAddModule(data); });

    this->SetOnCommand(cmd2, [this](json::value data)
                       { this->OnRemoveModule(data); });
}

void ModuleRegistry::OnAddModule(json::value data)
{
    auto &obj = data.as_object();

    string uuid_str = obj.at("UUID").as_string().c_str();
    uint128_t uuid(uuid_str);

    string type = obj.at("type").as_string().c_str();

    this->AddModule(type, uuid);
}

void ModuleRegistry::OnChange(const string &command, shared_ptr<ModuleCore> module)
{

    json::object modData;
    modData["UUID"] = to_string(module->GetUUID());
    modData["type"] = module->type;

    ModuleCore::OnChange(command, modData);
}

void ModuleRegistry::AddModule(string type, uint128_t UUID, bool sync)
{
    auto it = this->modules.find(UUID);
    if (it != this->modules.end())
    {
        cout << "Exists already " << endl;
        return;
    }

    void *rawPtr = ModuleTypes.at(type)(&UUID);

    auto *basePtr = static_cast<ModuleCore *>(rawPtr);

    shared_ptr<ModuleCore> module(basePtr);
    module->outputFn = this->outputFn;
    this->modules[UUID] = module;

    if (sync)
    {

        json::object data;
        data["type"] = type;
        data["UUID"] = UUID.str();
        this->Output("ADD_MODULE", data);
    }

    this->OnChange("ADD_MODULE", module);
}

void ModuleRegistry::OnRemoveModule(json::value data)
{
    auto &obj = data.as_object();

    string uuid_str = obj.at("UUID").as_string().c_str();
    uint128_t uuid(uuid_str);

    this->RemoveModule(uuid);
}

void ModuleRegistry::RemoveModule(uint128_t UUID, bool sync)
{
    auto it = this->modules.find(UUID);
    if (it == this->modules.end())
    {
        cout << UUID << " module doesn't exist " << endl;
        return;
    }

    auto mod = it->second;
    this->modules.erase(it);

    this->OnChange("REMOVE_MODULE", mod);

    if (sync)
    {

        json::object data;
        data["UUID"] = UUID.str();
        this->Output("REMOVE_MODULE", data);
    }
}

shared_ptr<ModuleCore> ModuleRegistry::GetModule(uint128_t UUID)
{
    auto it = modules.find(UUID);
    if (it != modules.end())
        return it->second;
    cerr << "UUID doesn't exists " << endl;
    return nullptr;
}

void ModuleRegistry::SetState(json::value state)
{
    auto &obj = state.as_object();
    auto &modulesArray = obj.at("modulesData").as_array();
    for (const auto &moduleData : modulesArray)
    {
        auto &entry = moduleData.as_object();
        string uuid_str = entry.at("UUID").as_string().c_str();
        uint128_t uuid(uuid_str);
        string type = entry.at("type").as_string().c_str();
        this->AddModule(type, uuid);
    }
}

json::value ModuleRegistry::GetState()
{
    json::array modulesData;
    for (const auto &[UUID, module] : this->modules)
    {
        if (module->type == this->type)
            continue;
        json::object entry;
        entry["UUID"] = UUID.str();
        entry["type"] = module->type;
        modulesData.push_back(entry);
    }
    json::object result;
    result["modulesData"] = modulesData;
    return result;
}