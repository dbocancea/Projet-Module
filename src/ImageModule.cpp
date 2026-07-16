#include "ImageModule.hpp"

ImageModule::ImageModule( ) : TransformModule( )
{
    this->type = "ImageModule";
}

ImageModule::ImageModule( uuids::uuid UUID ) : TransformModule( UUID )
{
    this->type = "ImageModule";
    this->command["setImage"] =  "SET_IMAGE";
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

    this->setImage( new_im, sync );
}

void ImageModule::setImage( json::value im, bool sync )
{
    this->OnChange( this->command["setImage"], im );

    if( sync )
    {
        this->Output( this->command["setImage"], im );
    }
}

json::value ImageModule::GetState( )
{
    json::value transformState = this->TransformModule::GetState( );

    json::object obj = transformState.as_object( );

    obj["image"] = this->image;

    return obj;
}

void ImageModule::SetState( json::value state )
{
    if( !state.is_object( ) ) return;
    
    auto& obj = state.as_object( );
    auto it = obj.find( "image" );

    if( it != obj.end( ) )
        this->onSetImage( it->value( ) );

    this->TransformModule::SetState( state );
}