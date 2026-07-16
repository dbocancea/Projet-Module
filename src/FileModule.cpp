#include "FileModule.hpp"

FileModule::FileModule() : ModuleCore()
{
    this->type = "FileModule";
}

FileModule::FileModule(uuids::uuid UUID) : ModuleCore(UUID)
{
    this->type = "FileModule";
    this->command["updateFile"] = "UPDATE_FILE";
    this->SetOnCommand(this->command["updateFile"], [this](json::value data){
        this->OnUpdateFile(data); });
}

void FileModule::OnUpdateFile(json::value file)
{
    if( !file.is_object() ) return;
    json::object obj = file.as_object();

    if( obj.contains("file") && obj.at("file").is_object() )
        obj = obj.at("file").as_object();

    string name = obj.at("name").as_string().c_str();
    string type = obj.at("type").as_string().c_str();
    string data = obj.at("data").as_string().c_str();

    this->UpdateFile(name, type, data, false);
}

void FileModule::UpdateFile(string name, string type, string data, bool sync)
{
    this->file.data = data;
    this->file.name = name;
    this->file.type = type;

    json::object obj;
    obj["data"] = this->file.data;
    obj["type"] = this->file.type;
    obj["name"] = this->file.name;

    this->OnChange(this->command["updateFile"], obj);

    if (sync)
    {
        json::object wrap;
        wrap["file"] = obj;
        this->Output(this->command["updateFile"], wrap);
    }
        
    
}

File FileModule::GetFile()
{
    return this->file;
}

json::value FileModule::GetState()
{
    json::object file;
    file["data"] = this->file.data;
    file["type"] = this->file.type;
    file["name"] = this->file.name;

    json::object obj;
    obj["file"] = file;                    
    return obj;
}

void FileModule::SetState(json::value newState)
{
    if (newState.is_object())
    {
        this->OnUpdateFile(newState);
    }
}
