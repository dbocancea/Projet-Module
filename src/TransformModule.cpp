#include "TransformModule.hpp"

<<<<<<< HEAD
template<typename T> 
TransformModule<T>::TransformModule() 
=======

TransformModule::TransformModule() 
>>>>>>> TransformModule
{
    this->type = "TransformModule";
}

<<<<<<< HEAD
template<typename T> 
TransformModule<T>::TransformModule(uint128_t UUID) : ModuleCore(UUID)
=======
TransformModule::TransformModule( uint128_t UUID ) : ModuleCore( UUID )
>>>>>>> TransformModule
{
    this->type = "TransformModule";

    this->SetOnCommand( "UPDATE_TRANSFORM", [this]( json::value transform )
    {
<<<<<<< HEAD
        this->updateTransform(transform);
    });
}
template<typename T> 
void TransformModule<T>::updateTransform(vector<float> transform, bool sync = false)
{
        if(transform.size() >= 10)
        {
            this->translation[0] = transform[0];
            this->translation[1] = transform[1];
            this->translation[2] = transform[2];
=======
        this->updateTransform( transform );
    });
}

void TransformModule::updateTransform( json::value transform, bool sync = false )
{   
    if( !transform.is_array() ) return;
    auto& liste = transform.as_array();
    if( liste.size() >= 10 )
    {
        this->translation[0] = liste[0].to_number<float>();
        this->translation[1] = liste[1].to_number<float>();
        this->translation[2] = liste[2].to_number<float>();
>>>>>>> TransformModule

        this->rotation[0] = liste[3].to_number<float>();
        this->rotation[1] = liste[4].to_number<float>();
        this->rotation[2] = liste[5].to_number<float>();
        this->rotation[3] = liste[6].to_number<float>();

        this->scale[0] = liste[7].to_number<float>();
        this->scale[1] = liste[8].to_number<float>();
        this->scale[2] = liste[9].to_number<float>();
    }

    if( sync )
        this->Output( "UPDATE_TRANSFORM", transform );
}

<<<<<<< HEAD
template<typename T> 
tuple<array<float, TRANSLATION_SIZE>, array<float, ROTATION_SIZE>, array<float, SCALE_SIZE>> TransformModule<T>::getTransform()
=======
tuple<array<float, TRANSLATION_SIZE>, array<float, ROTATION_SIZE>, array<float, SCALE_SIZE>> TransformModule::getTransform()
>>>>>>> TransformModule
{
    return {translation, rotation, scale};
}

<<<<<<< HEAD
template<typename T> 
void TransformModule<T>::setState(map<string, vector<float>> state)
{
    auto it = state.find("transform");
    if(it != state.end())
        this->updateTransform(it->second);
}

template<typename T> 
map<string, vector<float>> TransformModule<T>::getState()
{
    return{
        {"transform", {translation[0], translation[1], translation[2], rotation[0], rotation[1], rotation[2], rotation[3], scale[0], scale[1], scale[2]}}
    };
}
=======
void TransformModule::setState( json::value state )
{
    if( !state.is_object() ) return;

    auto& obj = state.as_object();

    auto it = obj.find( "transform" );
    if( it != obj.end() )
        this->updateTransform( it->value() );
}

json::value TransformModule::getState()
{
    json::array liste = {translation[0], translation[1], translation[2], rotation[0], rotation[1], rotation[2], rotation[3], scale[0], scale[1], scale[2]};

    json::object obj;
    obj["transform"] = liste;

    return liste;
}
>>>>>>> TransformModule
