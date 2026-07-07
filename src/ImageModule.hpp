#ifndef IMAGE_MODULE_HPP
#define IMAGE_MODULE_HPP
#include "TransformModule.hpp"

class ImageModule : public TransformModule
{
    protected:
        json::value image;
    public:
        ImageModule( );
        ImageModule( uint128_t UUID );
        json::value getImage( );
        void onSetImage( json::value image, bool sync = false );
        void setImage( json::value image, bool sync = false );
        json::value getState( );
        void setState( json::value state );
};

#endif