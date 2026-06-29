#include "FileModule.hpp"
template <typename T>
FileModule<T>::FileModule() : ModuleCore<T>()
{
    this->type = "FileModule";
}
template <typename T>
FileModule<T>::FileModule( uint128_t UUID ) : ModuleCore<T>(UUID)
{
    this->type = "FileModule";
    string cmd = "UPDATE_FILE";
    this->command.push_back(cmd);
    this->SetOnCommand(cmd , [&](File file) {this->UpdateFile(file, false);}  );
}
template <typename T>
void FileModule<T>::UpdateFile(File file , bool sync )
{
    this->file = file;
    this->OnChange("UPDATE_FILE" , this->file );

    if( sync )
        this->outputFn(pair<string, File >{"UPDATE_FILE" , file});
}
template <typename T>
File FileModule<T>::getFile()
{
    return this->file;
}
template <typename T>
void FileModule<T>::setState( T newState) {
        this->UpdateFile(newState , 0);
    }

template class FileModule<File>;