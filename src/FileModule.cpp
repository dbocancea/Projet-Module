#include "FileModule.hpp"

FileModule::FileModule()
{
    this->type = "FileModule";
}

FileModule::FileModule( uint128_t UUID ) : ModuleCore(UUID)
{
    this->type = "FileModule";
    string cmd = "UPDATE_FILE";
    this->command.push_back(cmd);
    this->SetOnCommand(cmd , [&](vector<float> file) {this->UpdateFile(file, false);}  );
}

void FileModule::UpdateFile(vector<float> file , bool sync)
{
    this->file = file;
    this->OnChange("UPDATE_FILE" , this->file );

    if( sync )
        this->outputFn(pair<string, vector<float> >{"UPDATE_FILE" , file});
}