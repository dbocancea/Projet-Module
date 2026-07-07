#include "ModuleRegistry.hpp"

ModuleRegistry::ModuleRegistry() {}

ModuleRegistry::ModuleRegistry(function<void(json::value)> outputFn) : ModuleCore(0)
{
    shared_ptr<ModuleCore> selfPtr(this, [](ModuleCore*){ });
    this->modules.insert({0 , selfPtr });

    this->command["addModule"] = "ADD_MODULE";
    this->command["remouveModule"] = "REMOUVE_MODULE";
    this->outputFn = outputFn;
    this->SetOnCommand(this->command["addModule"], [this](json::value data)
                       { this->OnAddModule(data); });

    this->SetOnCommand(this->command["remouveModule"], [this](json::value data)
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
    json::object data;
    data["type"] = type;
    data["UUID"] = UUID.str();
    
    this->OnChange(this->command["addModule"], data);

    if (sync)
        this->Output(this->command["addModule"], data);
    

    
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

    json::object data;
    data["UUID"] = UUID.str();

    this->OnChange(this->command["remouveModule"], data);

    if (sync)
        this->Output(this->command["remouveModule"], data);
    
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