#ifndef CAMERAMODULE_HPP
#define CAMERAMODULE_HPP
#include "Core/ModuleCore.hpp"

class CameraModule : public ModuleCore
{
    protected:
        float far{};
        float fov{};
        float near{};
        float aspect{};
    public:
        CameraModule();
};
  
#endif
