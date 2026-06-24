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
    
    this->SetOnCommand(this->command[this->command.size()-1] , [&](int value ) {this->UpdateValue(value);} );
}

void ScalarModule::UpdateValue(int value)
{
    cout << "ScalarModule - UpdateValue" << endl;
    this->value = value;
    this->OnChange(this->command[this->command.size()-1] , value);
}