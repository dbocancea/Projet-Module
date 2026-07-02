#include "ModuleCore.hpp"

ModuleCore::ModuleCore() 
{
    this->type = "ModuleCore";
}

ModuleCore::ModuleCore(uint128_t UUID)
{   
    string cmd = "SET_STATE";
    this->command.push_back(cmd);
    this->type = "ModuleCore";
    this->UUID = UUID;
    this->SetOnCommand(cmd, [this]( json::value obj ) {this->SetState(obj);} );
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
    else
        cout << this->UUID << " has no member " << endl;
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
    else
        cout << this->UUID << " has no member " << endl;
}

json::value ModuleCore::GetState ( )
{
	return json::object();
}
void ModuleCore::SetState (json::value state )
{
	return;
}

uint128_t ModuleCore::GetUUID()
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
    payload["moduleUUID"] = this->UUID.str();
    payload["command"] = command;
    payload["data"] = data;
    return payload;
}

void ModuleCore::Output(const string& command, json::value data)
{
    json::value payload = this->Encode(command, data);
    if (this->outputFn)
        this->outputFn(payload);
}