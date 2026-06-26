#ifndef FILEMODULE_HPP
#define FILEMODULE_HPP
#include "Core/ModuleCore.hpp"

struct str_File
{
    string name;
    string type;
    vector<float> data;
};

using File = struct str_File;

template <typename T>
class FileModule : public ModuleCore<T>
{   
    protected:
        File file;
    public:
        FileModule();
        FileModule(uint128_t UUID);
        void UpdateFile(File file , bool sync);
        File getFile();
        void setState(T state);
        File getState();
};  

#endif