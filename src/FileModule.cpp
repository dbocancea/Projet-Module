#include "FileModule.hpp"

FileModule::FileModule() : ModuleCore()
{
    this->type = "FileModule";
}

FileModule::FileModule(uint128_t UUID) : ModuleCore(UUID)
{
    this->type = "FileModule";
    this->command["updateFile"] = "UPDATE_FILE";
    this->SetOnCommand(this->command["updateFile"], [this](json::value data)
                       {
        json::object obj = data.as_object();
        this->OnUpdateFile(obj); });
}

void FileModule::OnUpdateFile(json::value file)
{
    json::object obj = file.as_object();
    string name = obj["name"].as_string().c_str();
    string type = obj["type"].as_string().c_str();
    string data = obj["data"].as_string().c_str();

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
        this->Output(this->command["updateFile"], obj);
    
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
    return file;
}

void FileModule::SetState(json::value newState)
{
    if (newState.is_object())
    {
        auto obj = newState.as_object();
        this->OnUpdateFile(obj);
    }
}
