#include "CameraModule.hpp"

CameraModule::CameraModule() : TransformModule( )
{
    this->type = "CameraModule";
}

CameraModule::CameraModule( uuids::uuid UUID ) : TransformModule( UUID )
{
    this->type = "CameraModule";
    this->command["updateCamera"] =  "UPDATE_CAMERA";
    this->SetOnCommand( this->command["updateCamera"], [this]( json::value camera )
    {
        this->onUpdateCamera( camera );
    });
}

void CameraModule::onUpdateCamera( json::value camera_json, bool sync )
{
    if( !camera_json.is_array( ) ) return;
    auto& liste = camera_json.as_array( );
    if( liste.size( ) == 4 )
    {
        this->camera_data.fov = liste[0].to_number<float>();
        this->camera_data.aspect = liste[1].to_number<float>();
        this->camera_data.myNear = liste[2].to_number<float>();
        this->camera_data.myFar = liste[3].to_number<float>();
    }

    this->updateCamera( this->camera_data, sync );
}

void CameraModule::updateCamera( CameraData new_data, bool sync )
{
    this->camera_data = new_data;
    json::value camera_update = {this->camera_data.fov, this->camera_data.aspect, this->camera_data.myNear, this->camera_data.myFar};

    this->OnChange( this->command["updateCamera"], camera_update );

    if( sync )
        this->Output( this->command["updateCamera"], camera_update );
}

CameraModule::CameraData CameraModule::getCamera( )
{
    return this->camera_data;
}

void CameraModule::setState( json::value state )
{
    if( !state.is_object( ) ) return;

    auto& obj = state.as_object( );

    auto it = obj.find( "camera" );
    if( it != obj.end( ) )
        this->onUpdateCamera( it->value( ) );

    this->TransformModule::setState( state );
}

json::value CameraModule::getState( )
{
    json::value transform_state = this->TransformModule::getState( );

    json::object obj = transform_state.as_object( );

    json::array liste = {this->camera_data.fov, this->camera_data.aspect, this->camera_data.myNear, this->camera_data.myFar};

    obj["camera"] = liste;

    return obj;
}