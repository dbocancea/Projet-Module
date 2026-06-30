#include "TriggerModule.hpp"

TriggerModule::TriggerModule()
{
    this->type = "TriggerModule";
}

TriggerModule::TriggerModule(uint128_t UUID){
    this->type = "TriggerModule";
    this->command.push_back("TRIGGER");
    cout << "TriggerModule - constructor";
    this->SetOnCommand("TRIGGER", [this](bool bl){this->trigger(false);});

}

void TriggerModule::trigger(bool sync){
    this->OnChange("TRIGGER", true);

    if(sync){
        this->outputFn(pair<string, bool>{"TRIGGER", true});
    }
}
