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
        CameraData camera_data{};
    public:
        CameraModule( );
        CameraModule( uuids::uuid UUID );
        void onUpdateCamera( json::value camera, bool sync = false );
        void updateCamera( CameraData camera, bool sync = false );
        CameraData getCamera( );
        void SetState( json::value state );
        json::value GetState( );
};

#endif