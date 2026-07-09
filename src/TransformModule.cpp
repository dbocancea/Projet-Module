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
    if( !transform.is_object() ) return;
    auto& outer = transform.as_object();

    // Accept either {"translation":...,...} directly, or {"transform": {...}} wrapped
    const boost::json::object* objPtr = &outer;
    boost::json::object unwrapped;
    if (outer.contains("transform")) {
        unwrapped = outer.at("transform").as_object();
        objPtr = &unwrapped;
    }
    auto& obj = *objPtr;

    if (!obj.contains("translation") || !obj.contains("rotation") || !obj.contains("scale"))
        return;

    auto& t = obj.at("translation").as_array();
    auto& r = obj.at("rotation").as_array();
    auto& s = obj.at("scale").as_array();
    if (t.size() < 3 || r.size() < 4 || s.size() < 3) return;

    TransformData new_data;
    new_data.translation[0] = t[0].to_number<float>();
    new_data.translation[1] = t[1].to_number<float>();
    new_data.translation[2] = t[2].to_number<float>();
    new_data.rotation[0] = r[0].to_number<float>();
    new_data.rotation[1] = r[1].to_number<float>();
    new_data.rotation[2] = r[2].to_number<float>();
    new_data.rotation[3] = r[3].to_number<float>();
    new_data.scale[0] = s[0].to_number<float>();
    new_data.scale[1] = s[1].to_number<float>();
    new_data.scale[2] = s[2].to_number<float>();

    this->updateTransform( new_data, sync );
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

    this->OnChange( this->command["updateTransform"], transform_update );

    if( sync )
        this->Output( this->command["updateTransform"], transform_update );
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
