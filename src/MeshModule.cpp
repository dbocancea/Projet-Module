#include "MeshModule.hpp"

MeshModule::MeshModule(){}

MeshModule::MeshModule(uint128_t UUID) : FileModule(UUID)
{
    this->type="MeshModule";
    cout << "MeshModule - constructor" << endl;
    this->command.push_back("CLEAR");
    this->command.push_back("UPDATE_TRANSFORM");
    this->command.push_back("UPDATE_BOUNDINGBOX");
}

json::value MeshModule::getState()
{
    return FileModule::GetState();
}

void MeshModule::SetState(json::value state)
{
    FileModule::SetState(state);
}