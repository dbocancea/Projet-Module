#include "TransformModule.hpp"


TransformModule::TransformModule( ) 
{
    this->type = "TransformModule";
}

TransformModule::TransformModule( uuids::uuid  UUID ) : ModuleCore( UUID )
{
    this->type = "TransformModule";
    this->command["updateTransform"] = "UPDATE_TRANSFORM";
    this->SetOnCommand( this->command["updateTransform"], [this]( json::value transform )
    {
        this->onUpdateTransform( transform );
    });
}

void TransformModule::onUpdateTransform( json::value transform, bool sync )
{   
    if( !transform.is_object( ) ) return;
    auto& obj = transform.as_object( );
    auto it = obj.find( "transfoem" );
    if( it == obj.end( ) || !it->value( ).is_object( ) ) return;

    if (!obj.contains("translation") || !obj.contains("rotation") || !obj.contains("scale"))
        return;

    auto& trans = it->value( ).as_object( );
    if( trans.contains( "translation" ) )
        for( int i = 0; i < TRANSLATION_SIZE; ++i )
            this->transform_data.translation[i] = trans.at( "translation" ).to_number<float>( );
    
    if( trans.contains( "rotation" ) )
        for( int i = 0; i < ROTATION_SIZE; ++i)
            this->transform_data.rotation[i] = trans.at( "rotation").to_number<float>( );

    if( trans.contains( "scale" ) )
        for( int i = 0; i < SCALE_SIZE; ++i)
            this->transform_data.scale[i] = trans.at( "scale").to_number<float>( );


    this->updateTransform( transform_data, sync );
}

void TransformModule::updateTransform( TransformData new_data, bool sync )
{   
    this->transform_data = new_data;

    json::object transform_update;
    transform_update["translation"] = json::array{transform_data.translation[0], transform_data.translation[1], transform_data.translation[2]};
<<<<<<< HEAD
    transform_update["rotation"] = json::array{transform_data.rotation[0], transform_data.rotation[1], transform_data.rotation[2], transform_data.rotation[3]};
    transform_update["scale"] = json::array{transform_data.scale[0], transform_data.scale[1], transform_data.scale[2]};

    this->OnChange( this->command["updateTransform"], transform_update );
    if( sync )
    {
        json::object wrapped;

        wrapped["transform"] = transform_update;

        this->Output( this->command["updateTransform"], wrapped );
    }

}


TransformModule::TransformData TransformModule::getTransform( )
{
    return this->transform_data;
}

void TransformModule::SetState( json::value state )
{
    if( !state.is_object( ) ) return;

    auto& obj = state.as_object( );

    auto it = obj.find( "transform" );
    if( it != obj.end( ) )
        this->onUpdateTransform( it->value( ) );
}

json::value TransformModule::GetState()
{
    json::object transform;
    transform["translation"] = json::array{transform_data.translation[0], transform_data.translation[1], transform_data.translation[2]};
    transform["rotation"] = json::array{transform_data.rotation[0], transform_data.rotation[1], transform_data.rotation[2], transform_data.rotation[3]};
    transform["scale"] = json::array{transform_data.scale[0], transform_data.scale[1], transform_data.scale[2]};

    json::object obj;
    obj["transform"] = transform;
    return obj;
}