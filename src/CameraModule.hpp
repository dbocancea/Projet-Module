#ifndef CAMERAMODULE_HPP
#define CAMERAMODULE_HPP
#include "Core/ModuleCore.hpp"
#include "TransformModule.hpp"
#include <tuple>

class CameraModule : public TransformModule<vector<float>>
{
    protected:
        float fov{};
        float aspect{};
        float myNear{};
        float myFar{};
    public:
        CameraModule();
        CameraModule(uint128_t UUID);
        void updateCamera(vector<float> camera, bool sync = false);
        tuple<float, float, float, float> getCamera();
        void setState(map<string, vector<float>> state);
        map<string, vector<float>> getState();
};

#endif