#ifndef CAMERAMODULE_HPP
#define CAMERAMODULE_HPP
#include "Core/ModuleCore.hpp"
#include "TransformModule.hpp"
#include <tuple>

class CameraModule : public TransformModule
{
    protected:
        float fov{};
        float aspect{};
        float myNear{};
        float myFar{};
    public:
        CameraModule();
        CameraModule(uint128_t UUID);
        void updateCamera(json::value camera, bool sync = false);
        tuple<float, float, float, float> getCamera();
        void setState(json::value state);
        json::value getState();
};

#endif