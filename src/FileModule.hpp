#ifndef FILEMODULE_HPP
#define FILEMODULE_HPP
#include "Core/ModuleCore.hpp"

class FileModule : public ModuleCore
{   
    protected:
        json::object file;
    public:
        FileModule();
        FileModule(uint128_t UUID);
        void UpdateFile(json::value file , bool sync = false );
        json::value GetFile();
        void SetState(json::value state) override;
        json::value  GetState() override;
};  

#endif