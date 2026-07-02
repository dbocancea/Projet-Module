#include "Vector3Module.hpp"

Vector3Module::Vector3Module()
{
    this->type = "Vector3Module";
}

Vector3Module::Vector3Module(uint128_t UUID) : ModuleCore(UUID)
{
    cout << "Vector3Module - constructor" << endl;
    this->type = "Vector3Module";
    this->command.push_back("UPDATE_VECTOR");

    this->SetOnCommand("UPDATE_VECTOR", [this](json::value data)
        { 
            auto& obj = data.as_object();
            this->UpdateVector(obj.at("vector")); 
});
}

void Vector3Module::UpdateVector(json::value vector, bool sync)
{
    json::array array_json = vector.as_array();
    cout << "Vector3Module - updateVector" << endl;

    for (int i = 0; i < static_cast<int>(this->vector.size()); i++)
        this->vector[i] = static_cast<int>(array_json[i].as_int64());
    
    json::object data;
    data["vector"] = array_json;
    this->OnChange("UPDATE_VECTOR", data);

    if( sync )   
        this->Output("UPDATE_VECTOR" , data );
    
}

array<int, 3> Vector3Module::GetVector()
{
    return this->vector;
}

json::value Vector3Module::GetState()
{
    json::object vector;
    json::array json_arr;

    for (int num : this->vector) 
        json_arr.push_back(num);
    
    vector["vector"] = json_arr;
    return vector;
}
void Vector3Module::SetState( json::value vector)
{
    if( vector.is_object() )
    {
        auto obj = vector.as_object();
        this->UpdateVector(obj.at("vector"));
    }
    
}