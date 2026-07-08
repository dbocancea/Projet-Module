#include "TriggerModule.hpp"


TriggerModule::TriggerModule()
{
    this->type = "TriggerModule";
}

TriggerModule::TriggerModule(uuids::uuid UUID) : ModuleCore(UUID)
{
    this->type = "TriggerModule";
    this->command["trigger"] = "TRIGGER";
    cout << "TriggerModule - constructor";
    this->SetOnCommand(this->command["trigger"], [this](json::value v){
        (void)v;
        this->trigger();});

}

void TriggerModule::trigger(bool sync){
    this->OnChange(this->command["trigger"], json::object());

    if(sync){
        this->Output(this->command["trigger"], json::object());
    }
}
