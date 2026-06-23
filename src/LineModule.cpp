#include "LineModule.hpp"


LineModule::LineModule() {};
LineModule::LineModule(uint128_t)
{
    this->type = "LineModule";

    this->origin = {0.,0.,0.};
    this->end = {0.,0.,0.};

    string updLine = "UPDATE_LINE";
    this->command.push_back(updLine);

    this->SetOnCommand(updLine, [&](vector<float> data) {this->updateLine(data);});
 
}

void LineModule::updateLine(std::vector<float> line) // not possible to do for now: JSON (not vect) needed to work properly
{
    cout << "LineModule - updateLine" << endl;
}
