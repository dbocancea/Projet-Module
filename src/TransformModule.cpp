#include "TransformModule.hpp"

template<typename T> 
TransformModule<T>::TransformModule() 
{
    this->type = "TransformModule";
}

template<typename T> 
TransformModule<T>::TransformModule(uint128_t UUID) : ModuleCore(UUID)
{
    this->type = "TransformModule";

    this->SetOnCommand("UPDATE_TRANSFORM", [this](vector<float> transform)
    {
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

            this->rotation[0] = transform[3];
            this->rotation[1] = transform[4];
            this->rotation[2] = transform[5];
            this->rotation[3] = transform[6];

            this->scale[0] = transform[7];
            this->scale[1] = transform[8];
            this->scale[2] = transform[9];
        }

        if(sync)
            if(this->outputFn)
                this->outputFn(pair<string, vector<float>>("UPDATE_TRANSFORM", transform));
}

template<typename T> 
tuple<array<float, TRANSLATION_SIZE>, array<float, ROTATION_SIZE>, array<float, SCALE_SIZE>> TransformModule<T>::getTransform()
{
    return {translation, rotation, scale};
}

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