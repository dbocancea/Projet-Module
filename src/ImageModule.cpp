#include "ImageModule.hpp"

ImageModule::ImageModule() : TransformModule(0)
{
    this->type = "ImageModule";
}

ImageModule::ImageModule( uint128_t UUID ) : TransformModule( UUID )
{
    this->type = "ImageModule";
    this->SetOnCommand( "SET_IMAGE", [this]( json::value image )
    {
        this->setImage( image );
    });
}

json::value ImageModule::getImage()
{
    return this->image;
}

void ImageModule::setImage( json::value newIm, bool sync )
{
    this->image = newIm;
    this->OnChange( "SET_IMAGE", newIm );

    if( sync )
    {
        this->Output( "SET_IMAGE", newIm );
    }
}

json::value ImageModule::getState()
{
    json::value transformState = this->TransformModule::getState();

    json::object obj = transformState.as_object();

    obj["image"] = this->image;

    return obj;
}

void ImageModule::setState(json::value state)
{
    if( !state.is_object() ) return;
    
    auto& obj = state.as_object();
    auto it = obj.find("camera");

    if( it != obj.end())
        this->setImage(it->value());

    this->TransformModule::setState(state);
}
