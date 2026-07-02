#include "ScalarModule.hpp"

ScalarModule::ScalarModule()
{
    this->type = "ScalarModule";
}

ScalarModule::ScalarModule(uint128_t UUID) : ModuleCore(UUID)
{
    cout << "ScalarModule - constructor" << endl;
    this->type = "ScalarModule";
    this->command.push_back("UPDATE_VALUE");
    
    this->SetOnCommand("UPDATE_VALUE" , [this](json::value data ) 
    {
        auto& obj = data.as_object();
        this->UpdateValue(obj.at("value"));
    });
}

void ScalarModule::UpdateValue(json::value value , bool sync)
{
    cout << "ScalarModule - UpdateValue" << endl;
    this->value = static_cast<int>(value.as_int64());

    json::object data;
    data["value"] = value;

    this->OnChange("UPDATE_VALUE" , value);

    if(sync)
         this->Output("UPDATE_VALUE" , data );
}

void ScalarModule::SetState(json::value newState)
{
    if( newState.is_object() )
    {
        auto obj = newState.as_object();
        this->UpdateValue(obj.at("value"));
    }
}

json::value ScalarModule::GetState()
{
    json::object status;

    status["value"] = this->value;

    return status;
}
int ScalarModule::GetValue()
{
    return this->value;
}