#include "TriggerModule.hpp"


TriggerModule::TriggerModule()
{
    this->type = "TriggerModule";
}

TriggerModule::TriggerModule(uint128_t UUID){
    this->type = "TriggerModule";
    this->command.push_back("TRIGGER");
    cout << "TriggerModule - constructor";
    this->SetOnCommand("TRIGGER", [this](json::value v){
        (void)v;
        this->trigger();});

}

void TriggerModule::trigger(bool sync){
    this->OnChange("TRIGGER", json::object());

    if(sync){
        this->Output("TRIGGER", json::object());
    }
}
