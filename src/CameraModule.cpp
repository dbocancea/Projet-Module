#include "CameraModule.hpp"

CameraModule::CameraModule() : TransformModule( 0 )
{
    this->type = "CameraModule";
}

CameraModule::CameraModule( uint128_t UUID ) : TransformModule( UUID )
{
    this->type = "CameraModule";

    this->SetOnCommand( "UPDATE_CAMERA", [this]( json::value camera )
    {
        this->onUpdateCamera( camera );
    });
}

void CameraModule::onUpdateCamera( json::value camera_json, bool sync )
{
    if( !camera_json.is_array() ) return;
    auto& liste = camera_json.as_array();
    if( liste.size() == 4 )
    {
        this->data.fov = liste[0].to_number<float>();
        this->data.aspect = liste[1].to_number<float>();
        this->data.myNear = liste[2].to_number<float>();
        this->data.myFar = liste[3].to_number<float>();
    }

    this->updateCamera( this->data, sync);
}

void CameraModule::updateCamera( CameraData new_data, bool sync )
{
    this->data = new_data;
    json::value camera_update = {this->data.fov, this->data.aspect, this->data.myNear, this->data.myFar};

    this->OnChange( "UPDATE_CAMERA", camera_update );

    if( sync )
        this->Output( "UPDATE_CAMERA", camera_update );
}

CameraModule::CameraData CameraModule::getCamera()
{
    return this->data;
}

void CameraModule::setState( json::value state )
{
    if( !state.is_object() ) return;

    auto& obj = state.as_object();

    auto it = obj.find( "camera" );
    if( it != obj.end() )
        this->onUpdateCamera( it->value() );

    this->TransformModule::setState( state );
}

json::value CameraModule::getState()
{
    json::value transform_state = this->TransformModule::getState( );

    json::object obj = transform_state.as_object( );

    json::array liste = {this->data.fov, this->data.aspect, this->data.myNear, this->data.myFar};

    obj["camera"] = liste;

    return obj;
}
