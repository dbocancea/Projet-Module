#include "LineModule.hpp"

namespace json = boost::json;
LineModule::LineModule() {};
LineModule::LineModule(uint128_t UUID)
{
    this->type = "LineModule";

    this->origin = {0.,0.,0.};
    this->end = {0.,0.,0.};

    string updLine = "UPDATE_LINE";
    this->command.push_back(updLine);

    this->SetOnCommand(updLine, [&](json::value data) {this->updateLine(data);});
 
}

void LineModule::updateLine(json::value line, bool sync) 
{
    cout << "LineModule - updateLine" << endl;
    json::object obj = line.get_object();

    if(obj.contains("origin") && obj.at("origin").is_array()){
        json::array arr = obj.at("origin").get_array();
        for(int i = 0; i < arr.size() && i < this->origin.size(); ++i){    
            this->origin[i] = json::value_to<float>(arr[i]);
        }
    }

    if(obj.contains("end") && obj.at("end").is_array()){
        json::array arr = obj.at("end").get_array();
        for(int i = 0; i < arr.size() && i < this->end.size(); ++i){    
            this->end[i] = json::value_to<float>(arr[i]);
        }
    }

    json::value updatedLine = this->getLine();
    this->OnChange("UPDATE_LINE", updatedLine);

    if(sync){
        json::object msgOutput;
        msgOutput["line"] = updatedLine;
        this->Output("UPDATE_LINE", msgOutput);
    }
}

json::value LineModule::getLine(){
    json::array originArr = {this->origin[0], this->origin[1], this->origin[2]};
    json::array endArr = {this->end[0], this->end[1], this->end[2]};
    return json::object({{"origin", originArr}, {"end", endArr}}) ;

}

json::value LineModule::getState(){
    return json::object({{"line", this->getLine()}});
}

void LineModule::setState(json::value state){
    this->updateLine(state.get_object().at("line"));
}
