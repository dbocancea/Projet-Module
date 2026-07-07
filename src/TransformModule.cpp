#include "TransformModule.hpp"


TransformModule::TransformModule( ) 
{
    this->type = "TransformModule";
}

TransformModule::TransformModule( uint128_t UUID ) : ModuleCore( UUID )
{
    this->type = "TransformModule";

    this->SetOnCommand( "UPDATE_TRANSFORM", [this]( json::value transform )
    {
        this->onUpdateTransform( transform );
    });
}

void TransformModule::onUpdateTransform( json::value transform, bool sync )
{   
    if( !transform.is_array( ) ) return;
    auto& liste = transform.as_array( );
    if( liste.size( ) >= 10 )
    {
        TransformData new_data;
        new_data.translation[0] = liste[0].to_number<float>( );
        new_data.translation[1] = liste[1].to_number<float>();
        new_data.translation[2] = liste[2].to_number<float>();

        new_data.rotation[0] = liste[3].to_number<float>( );
        new_data.rotation[1] = liste[4].to_number<float>( );
        new_data.rotation[2] = liste[5].to_number<float>( );
        new_data.rotation[3] = liste[6].to_number<float>( );

        new_data.scale[0] = liste[7].to_number<float>( );
        new_data.scale[1] = liste[8].to_number<float>( );
        new_data.scale[2] = liste[9].to_number<float>( );

        this->updateTransform( new_data, sync );
    }
}

void TransformModule::updateTransform( TransformData new_data, bool sync )
{   
    this->transform_data = new_data;
    json::value transform_update = 
    {
        this->transform_data.translation[0], 
        this->transform_data.translation[1],
        this->transform_data.translation[2],

        this->transform_data.rotation[0],
        this->transform_data.rotation[1],
        this->transform_data.rotation[2],
        this->transform_data.rotation[3],

        this->transform_data.scale[0],
        this->transform_data.scale[1],
        this->transform_data.scale[2],
    };

    this->OnChange( "UPDATE_TRANSFORM", transform_update );

    if( sync )
        this->Output( "UPDATE_TRANSFORM", transform_update );
}


TransformModule::TransformData TransformModule::getTransform( )
{
    return this->transform_data;
}

void TransformModule::setState( json::value state )
{
    if( !state.is_object( ) ) return;

    auto& obj = state.as_object( );

    auto it = obj.find( "transform" );
    if( it != obj.end( ) )
        this->onUpdateTransform( it->value( ) );
}

json::value TransformModule::getState( )
{
    json::array liste = 
    {
        this->transform_data.translation[0],
        this->transform_data.translation[1],
        this->transform_data.translation[2],

        this->transform_data.rotation[0],
        this->transform_data.rotation[1],
        this->transform_data.rotation[2],
        this->transform_data.rotation[3],

        this->transform_data.scale[0],
        this->transform_data.scale[1],
        this->transform_data.scale[2]
    };

    json::object obj;
    obj["transform"] = liste;

    return obj;
}
