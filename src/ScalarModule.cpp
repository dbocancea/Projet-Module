#include "ScalarModule.hpp"

ScalarModule::ScalarModule()
{
    this->type = "ScalarModule";
}

ScalarModule::ScalarModule(uuids::uuid UUID) : ModuleCore(UUID)
{
    cout << "ScalarModule - constructor" << endl;
    this->type = "ScalarModule";
    this->command["updateValue"] = "UPDATE_VALUE";
    
    this->SetOnCommand(this->command["updateValue"] , [this](json::value data ) 
    {
        this->OnUpdateValue(data);
    });
}

void ScalarModule::OnUpdateValue(json::value value)
{
    cout << "ScalarModule - UpdateValue" << endl;
    int val = static_cast<int>(value.as_object().at("value").as_int64());

    this->UpdateValue(val , false);
}

void ScalarModule::UpdateValue(int val , bool sync)
{
    this->value = val;

    json::object data;
    data["value"] = value;

    this->OnChange(this->command["updateValue"] , data);

    if(sync)
         this->Output(this->command["updateValue"] , data );
}

void ScalarModule::SetState(json::value newState)
{
    if( newState.is_object() )
    {
        auto obj = newState.as_object();
        this->OnUpdateValue(obj);
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