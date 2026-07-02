#include "FileModule.hpp"

FileModule::FileModule() : ModuleCore()
{
    this->type = "FileModule";
}

FileModule::FileModule( uint128_t UUID ) : ModuleCore(UUID)
{
    this->type = "FileModule";
    string cmd = "UPDATE_FILE";
    this->command.push_back(cmd);
    this->SetOnCommand(cmd , [this](json::value data) {
        json::object obj = data.as_object();
        this->UpdateFile(obj.at("file"));}  
    );
}

void FileModule::UpdateFile(json::value file , bool sync )
{
    this->file = file.as_object();
    this->OnChange("UPDATE_FILE" , this->file );

    if( sync )
    {   
        json::object data;
        data["file"] = this->file;
        this->Output("UPDATE_FILE" , data );
    }
       
}

json::value FileModule::GetFile()
{   
    return this->file;
}

json::value FileModule::GetState()
{   
    json::object file;
    file["file"] = this->file;
    return file;
}

void FileModule::SetState( json::value newState) 
{
    if( newState.is_object() )
    {
        auto obj = newState.as_object();
        this->UpdateFile(obj["file"] );
    }
        
}
