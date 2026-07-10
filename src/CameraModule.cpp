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

void CameraModule::onUpdateCamera(json::value camera_json, bool sync)
{
    if (!camera_json.is_object()) {
        if (camera_json.is_array()) {
            // legacy array-shape fallback (unlikely needed, kept for safety)
            auto& liste = camera_json.as_array();
            if (liste.size() == 4) {
                this->camera_data.fov    = liste[0].to_number<float>();
                this->camera_data.aspect = liste[1].to_number<float>();
                this->camera_data.myNear = liste[2].to_number<float>();
                this->camera_data.myFar  = liste[3].to_number<float>();
                this->updateCamera(this->camera_data, sync);
            }
        }
        return;
    }

    auto& outer = camera_json.as_object();
    const boost::json::object* objPtr = &outer;
    boost::json::object unwrapped;
    if (outer.contains("camera")) {              // <-- unwrap {"camera": {...}} envelope
        unwrapped = outer.at("camera").as_object();
        objPtr = &unwrapped;
    }
    auto& obj = *objPtr;

    if (obj.contains("fov"))    this->camera_data.fov    = obj.at("fov").to_number<float>();
    if (obj.contains("aspect")) this->camera_data.aspect = obj.at("aspect").to_number<float>();
    if (obj.contains("near"))   this->camera_data.myNear = obj.at("near").to_number<float>();
    if (obj.contains("far"))    this->camera_data.myFar  = obj.at("far").to_number<float>();

    this->updateCamera(this->camera_data, sync);
}

void CameraModule::updateCamera(CameraData new_data, bool sync)
{
    this->camera_data = new_data;

    json::object camera_obj;
    camera_obj["fov"]    = this->camera_data.fov;
    camera_obj["aspect"] = this->camera_data.aspect;
    camera_obj["near"]   = this->camera_data.myNear;
    camera_obj["far"]    = this->camera_data.myFar;

    this->OnChange(this->command["updateCamera"], camera_obj);

    if (sync) {
        json::object wrapped;
        wrapped["camera"] = camera_obj;              // <-- wrap for the wire, matches JS
        this->Output(this->command["updateCamera"], wrapped);
    }
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