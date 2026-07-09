#ifndef FILEMODULE_HPP
#define FILEMODULE_HPP
#include "Core/ModuleCore.hpp"

struct str_File 
{
    string name;
    string type;
    string data;
};

using File = struct str_File;

class FileModule : public ModuleCore
{   
    protected:
        File file;
    public:
        FileModule();
        FileModule(uuids::uuid UUID);
        void UpdateFile(string name , string type , string data , bool sync = false );
        void OnUpdateFile(json::value file );
        File GetFile();
        void SetState(json::value state) override;
        json::value  GetState() override;
};  

#endif