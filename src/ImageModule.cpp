#include "ImageModule.hpp"

ImageModule::ImageModule( ) : TransformModule( 0 )
{
    this->type = "ImageModule";
}

ImageModule::ImageModule( uint128_t UUID ) : TransformModule( UUID )
{
    this->type = "ImageModule";
    this->SetOnCommand( "SET_IMAGE", [this]( json::value image )
    {
        this->onSetImage( image );
    });
}

json::value ImageModule::getImage( )
{
    return this->image;
}

void ImageModule::onSetImage( json::value new_im, bool sync )
{
    this->image = new_im;
}

void ImageModule::setImage( json::value im, bool sync )
{
    this->OnChange( "SET_IMAGE", im );

    if( sync )
    {
        this->Output( "SET_IMAGE", im );
    }
}

json::value ImageModule::getState( )
{
    json::value transformState = this->TransformModule::getState( );

    json::object obj = transformState.as_object( );

    obj["image"] = this->image;

    return obj;
}

void ImageModule::setState( json::value state )
{
    if( !state.is_object( ) ) return;
    
    auto& obj = state.as_object( );
    auto it = obj.find( "camera" );

    if( it != obj.end( ) )
        this->setImage( it->value( ) );

    this->TransformModule::setState( state );
}
