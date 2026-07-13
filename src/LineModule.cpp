#include "LineModule.hpp"

namespace json = boost::json;
LineModule::LineModule() {};
LineModule::LineModule(uuids::uuid UUID) : ModuleCore(UUID)
{
    this->type = "LineModule";

    this->origin = {0.,0.,0.};
    this->end = {0.,0.,0.};

    this->command["updateLine"] = "UPDATE_LINE";

    this->SetOnCommand(this->command["updateLine"], [&](json::value data) {this->OnUpdateLine(data);});
 
}

void LineModule::OnUpdateLine(json::value line) 
{
    json::object obj = line.get_object();
    vector<float> origintemp;
    vector<float> endtemp;
    if(obj.contains("origin") && obj.at("origin").is_array()){
        json::array arr = obj.at("origin").get_array();
        for(int i = 0; i < static_cast<int>(arr.size()); ++i){    
            origintemp[i] = json::value_to<float>(arr[i]);
        }
    }

    if(obj.contains("end") && obj.at("end").is_array()){
        json::array arr = obj.at("end").get_array();
        for(int i = 0; i < static_cast<int>(arr.size()); ++i){    
            endtemp[i] = json::value_to<float>(arr[i]);
        }
    }
    this->UpdateLine(origintemp , endtemp , false);
    
}

void LineModule::UpdateLine(vector<float> origin , vector<float> end, bool sync) 
{
    cout << "LineModule - updateLine" << endl;

    if(!origin.empty())
        for(int i = 0; i < static_cast<int>(origin.size()); ++i) 
            this->origin[i] = origin[i];
        
    if(!end.empty())
        for(int i = 0; i < static_cast<int>(end.size()); ++i) 
            this->end[i] = end[i];

    json::value updatedLine = this->getLine();
    this->OnChange(this->command["updateLine"], updatedLine);

    if(sync){
        json::object msgOutput;
        msgOutput["line"] = updatedLine;
        this->Output(this->command["updateLine"], msgOutput);
    }
}

json::value LineModule::getLine(){
    json::array originArr = {this->origin[0], this->origin[1], this->origin[2]};
    json::array endArr = {this->end[0], this->end[1], this->end[2]};
    return json::object({{"origin", originArr}, {"end", endArr}}) ;

}

json::value LineModule::GetState(){
    return json::object({{"line", this->getLine()}});
}

void LineModule::SetState(json::value state){
    this->OnUpdateLine(state.get_object());
}
