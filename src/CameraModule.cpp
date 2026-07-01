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
        this->updateCamera( camera );
    });
}

void CameraModule::updateCamera( json::value camera, bool sync = false )
{
    if( !camera.is_object() ) return;
    auto& liste = camera.as_array();
    if( liste.size() == 4 )
    {
        this->fov = liste[0].to_number<float>();
        this->aspect = liste[1].to_number<float>();
        this->myNear = liste[2].to_number<float>();
        this->myFar = liste[3].to_number<float>();
    }

    this->OnChange( "UPDATE_CAMERA", camera );

    if(sync)
        this->Output( "UPDATE_CAMERA", camera );
}

tuple<float, float, float, float> CameraModule::getCamera()
{
    return {this->fov, this->aspect, this->myNear, this->myFar};
}

void CameraModule::setState( json::value state )
{
    if( !state.is_object() ) return;

    auto& obj = state.as_object();

    auto it = obj.find( "camera" );
    if( it != obj.end() )
        this->updateCamera( it->value() );
}

json::value CameraModule::getState()
{
    json::array liste = {this->fov, this->aspect, this->myNear, this->myFar};

    json::object obj;

    obj["camera"] = liste;

    return obj;
}
