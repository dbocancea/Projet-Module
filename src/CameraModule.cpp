#include "CameraModule.hpp"

CameraModule::CameraModule() : TransformModule()
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

void CameraModule::updateCamera( CameraData new_data, bool sync )
{
    this->camera_data = new_data;

    json::object camera_obj;
    camera_obj["fov"]   = this->camera_data.fov;
    camera_obj["aspect"] = this->camera_data.aspect;
    camera_obj["near"]  = this->camera_data.myNear;   
    camera_obj["far"]   = this->camera_data.myFar;

    this->OnChange( this->command["updateCamera"], camera_obj );

    if( sync ) {
        json::object wrapped;
        wrapped["camera"] = camera_obj;         
        this->Output( this->command["updateCamera"], wrapped );
    }
}

void CameraModule::onUpdateCamera( json::value data, bool sync )
{
    if( !data.is_object() ) return;
    auto& obj = data.as_object();
    auto it = obj.find("camera");
    if( it == obj.end() || !it->value().is_object() ) return;

    auto& cam = it->value().as_object();
    if( cam.contains("fov") )    this->camera_data.fov    = cam.at("fov").to_number<float>();
    if( cam.contains("aspect") ) this->camera_data.aspect = cam.at("aspect").to_number<float>();
    if( cam.contains("near") )   this->camera_data.myNear = cam.at("near").to_number<float>();
    if( cam.contains("far") )    this->camera_data.myFar  = cam.at("far").to_number<float>();

    this->updateCamera( this->camera_data, sync );
}
CameraModule::CameraData CameraModule::getCamera( )
{
    return this->camera_data;
}

void CameraModule::SetState( json::value state )
{
    if( !state.is_object( ) ) return;

    auto& obj = state.as_object( );

    auto it = obj.find( "camera" );
    if( it != obj.end( ) )
        this->onUpdateCamera( it->value( ) );

    this->TransformModule::SetState( state );
}

json::value CameraModule::GetState( )
{
    json::value transform_state = this->TransformModule::GetState( );

    json::object obj = transform_state.as_object( );

    json::array liste = {this->camera_data.fov, this->camera_data.aspect, this->camera_data.myNear, this->camera_data.myFar};

    obj["camera"] = liste;

    return obj;
}