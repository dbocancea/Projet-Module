#ifndef TRANSFORMMODULE_HHP
#define TRANSFORMMODULE_HHP

#define TRANSLATION_SIZE 3
#define ROTATION_SIZE 4
#define SCALE_SIZE 3

#include "Core/ModuleCore.hpp"
#include <array>

class TransformModule : public ModuleCore
{
    public:
        struct TransformData
        {
            array<float, TRANSLATION_SIZE> translation {};
            array<float, ROTATION_SIZE> rotation {};
            array<float, SCALE_SIZE> scale {};
        };
    protected:
        TransformData transform_data {};
    public:
        TransformModule( );
        TransformModule(uuids::uuid UUID );
        void updateTransform( TransformData transform, bool sync = false );
        void onUpdateTransform( json::value transform, bool sync = false );
        TransformData getTransform( );
        json::value getState( );
        void setState( json::value state );
};

#endif