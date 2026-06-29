#include "LineModule.hpp"


LineModule::LineModule() {};
LineModule::LineModule(uint128_t UUID) : ModuleCore(UUID)
{
    this->type = "LineModule";

    this->origin = {0.,0.,0.};
    this->end = {0.,0.,0.};

    string updLine = "UPDATE_LINE";
    this->command.push_back(updLine);

    this->SetOnCommand(updLine, [&](pair<vector<float>, vector<float>> data) {this->updateLine(data);});
 
}

void LineModule::updateLine(pair<vector<float>, vector<float>> line) 
{
    cout << "LineModule - updateLine" << endl;

    if(!line.first.empty()){
        this->origin = line.first;
    }

    if(!line.second.empty()){
        this->end = line.second;
    }

    pair<vector<float>, vector<float>> updatedLine = {this->origin, this->end};
    this->OnChange("UPDATE_LINE", updatedLine);

    if(this->outputFn){
        this->outputFn(pair<string, pair<vector<float>, vector<float>>>{"UPDATE_LINE", updatedLine});
    }
}

pair<vector<float>, vector<float>> LineModule::getLine(){
    return {this->origin, this->end};
}

pair<vector<float>, vector<float>> LineModule::getState(){
    return this->getLine();
}

void LineModule::setState(pair<vector<float>, vector<float>> state){
    this->updateLine(state);
}
