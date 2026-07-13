#include "Vector3Module.hpp"

Vector3Module::Vector3Module()
{
    this->type = "Vector3Module";
}

Vector3Module::Vector3Module(uuids::uuid UUID) : ModuleCore(UUID)
{
    cout << "Vector3Module - constructor" << endl;
    this->type = "Vector3Module";
    this->command["updateVector"] = "UPDATE_VECTOR";

    this->SetOnCommand(this->command["updateVector"], [this](json::value data)
        { 
            auto& obj = data.as_object();
            this->OnUpdateVector(obj.at("vector")); 
});
}

void Vector3Module::OnUpdateVector(json::value vector)
{
    json::array array_json = vector.as_array();
    array<int, 3> vect;
    for (int i = 0; i < static_cast<int>(vect.size()); i++)
        vect[i] = static_cast<int>(array_json[i].as_int64());
    
    this->UpdateVector(vect , 0);
    
}

void Vector3Module::UpdateVector(array<int, 3> vector, bool sync)
{

    for (int i = 0; i < static_cast<int>(vector.size()); i++)
        this->vector[i] = vector[i];
    json::value jv = json::value_from(vector);
    json::object data;
    data["vector"] = jv;
    this->OnChange(this->command["updateVector"], data);

    if( sync )   
        this->Output(this->command["updateVector"] , data );
    
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
        this->OnUpdateVector(obj);
    }
    
}