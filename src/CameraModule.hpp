#ifndef CAMERAMODULE_HPP
#define CAMERAMODULE_HPP
#include "Core/ModuleCore.hpp"
#include "TransformModule.hpp"

class CameraModule : public TransformModule
{
    public:
        struct CameraData
        {
            float fov;
            float aspect;
            float myNear;
            float myFar;
        };
    protected:
        CameraData data{};
    public:
        CameraModule( );
        CameraModule( uint128_t UUID );
        void onUpdateCamera( json::value camera, bool sync = false );
        void updateCamera( CameraData camera, bool sync = false );
        CameraData getCamera( );
        void setState( json::value state );
        json::value getState( );
};

#endif