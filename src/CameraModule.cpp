#include <iostream>
#include "CameraModule.hpp"

CameraModule::CameraModule() : TransformModule(0)
{
    this->type = "CameraModule";
}

CameraModule::CameraModule(uint128_t UUID) : TransformModule(UUID)
{
    this->type = "CameraModule";

    this->SetOnCommand("UPDATE_CAMERA", [this](vector<float> camera)
    {
        this->updateCamera(camera, false);
    });
}

void CameraModule::updateCamera(vector<float> camera, bool sync)
{
    if(camera.size() == 4)
    {
        this->fov = camera[0];
        this->aspect = camera[1];
        this->myNear = camera[2];
        this->myFar = camera[3];
    }

    if(sync)
        if(this->outputFn)
            this->outputFn(pair<string, vector<float>>("UPDATE_CAMERA", camera));
}

tuple<float, float, float, float> CameraModule::getCamera()
{
    return{this->fov, this->aspect, this->myNear, this->myFar};
}

void CameraModule::setState(map<string, vector<float>> state)
{
    auto it = state.find("camera");
    if(it != state.end())
        this->updateCamera(it->second, false);
}

map<string, vector<float>> CameraModule::getState()
{
    return {
        {"camera", {this->fov, this->aspect, this->myNear, this->myFar}}
    };
}
