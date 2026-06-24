#ifndef FILEMODULE_HPP
#define FILEMODULE_HPP
#include "Core/ModuleCore.hpp"

class FileModule : public ModuleCore<vector<float>>
{   
    protected:
        vector<float> file;
    public:
        FileModule();
        FileModule(uint128_t UUID);
        void UpdateFile(vector<float> file , bool sync);
        vector<float> getFile();
};  

#endif