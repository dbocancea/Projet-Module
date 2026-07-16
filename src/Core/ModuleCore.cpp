#include "ModuleCore.hpp"

ModuleCore::ModuleCore() 
{
    this->type = "ModuleCore";
}

ModuleCore::ModuleCore(uuids::uuid UUID)
{   
    this->command["setState"] = "SET_STATE";
    this->type = "ModuleCore";
    this->UUID = UUID;
    this->SetOnCommand(this->command["setState"], [this]( json::value obj ) {this->SetState(obj);} );
}

void ModuleCore::SetOnCommand(const string& command, function<void(json::value)> callback)
{
    auto it = this->commandCallBack.find(command);
    if (it == this->commandCallBack.end())
        this->commandCallBack.insert( {command, vector < function<void(json::value)> >{} } );
    commandCallBack[command].push_back(callback);
}

void ModuleCore::OnCommand(const string& command, json::value data)
{
    auto it = this->commandCallBack.find(command);
    if (it != this->commandCallBack.end())
        for (auto callback_temp : it->second)
            callback_temp(data);
}

void ModuleCore::SetOnChange(const string& command, function<void(json::value)> callback)
{
    auto it = this->changeCallBack.find(command);
    if (it == this->changeCallBack.end())
        this->changeCallBack.insert( {command, vector < function < void (json::value ) > >{} } );
    changeCallBack[command].push_back(callback);
}


void ModuleCore::OnChange(const string& command, json::value data)
{
    auto it = this->changeCallBack.find(command);
    if (it != this->changeCallBack.end())
        for (auto callback_temp : it->second)
            callback_temp(data);
}

json::value ModuleCore::GetState ( )
{
	return json::object();
}
void ModuleCore::SetState (json::value state )
{
	return;
}

uuids::uuid ModuleCore::GetUUID()
{
    return this->UUID;
}

void ModuleCore::SetOutputFn( function<void(json::value)> outputFn )
{
    this->outputFn = outputFn;
}

json::value ModuleCore::Encode(const string& command, json::value data)
{
    json::object payload;
    payload["moduleUUID"] = uuids::to_string(this->UUID);
    payload["command"] = command;
    payload["data"] = data;
    return payload;
}

string ModuleCore::GetType()
{
    return this->type;
}

void ModuleCore::Output(const string& command, json::value data)
{
    json::value payload = this->Encode(command, data);
    if (this->outputFn)
        this->outputFn(payload);
}

map<string , string> ModuleCore::GetCommand()
{
    return command;
}

json::value ModuleCore::outputState()
{
    json::value state = this->GetState(); 
    return this->Encode(this->command["setState"] , state);
}

void ModuleCore::input(json::value payload)
{
    json::object obj = payload.as_object();
    this->OnCommand(obj["command"].as_string().c_str() , obj["data"] );
}
