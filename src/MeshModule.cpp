#include "MeshModule.hpp"

MeshModule::MeshModule(){}

MeshModule::MeshModule(uuids::uuid UUID) : FileModule(UUID)
{
    this->type="MeshModule";
    cout << "MeshModule - constructor" << endl;

    this->command["clear"] = "CLEAR";
    this->command["updateTransform"] = "UPDATE_TRANSFORM";
    this->command["updateBoundingBox"] = "UPDATE_BOUNDINGBOX";
}

json::value MeshModule::getState()
{
    return FileModule::GetState();
}

void MeshModule::SetState(json::value state)
{
    FileModule::SetState(state);
}