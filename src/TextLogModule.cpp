#include "TextLogModule.hpp"

namespace json = boost::json;

TextLogModule::TextLogModule() : ModuleCore(0)
{
    this->type = "TextLogModule";
}

TextLogModule::TextLogModule(uint128_t UUID) : ModuleCore(UUID){
    cout << "TextLogModule - constructor" << endl;

    this->type = "TextLogModule";
    this->command.push_back("ADD_TEXT");
    this->command.push_back("REMOVE_TEXT");
    this->command.push_back("UPDATE_TEXT");
    this->command.push_back("CLEAR");
    this->SetOnCommand("ADD_TEXT", [this](json::value textlog)
    {
        this->addTextInternal(textlog.get_object().at("textLog").get_object());
    });
    this->SetOnCommand("REMOVE_TEXT", [this](json::value textlog)
    {
        this->removeText(textlog.get_object().at("textLog"));
    });
    this->SetOnCommand("UPDATE_TEXT", [this](json::value textlog)
    {
        this->updateText(textlog.get_object().at("textLog"));
    });

    this->SetOnCommand("CLEAR", [this](json::value textlog)
    {
        this->clear();
    });

    
}


json::object TextLogModule::getTextLog(uint128_t textUUID){
    return this->textLogs[textUUID];
}

void TextLogModule::addText(string text, bool sync){
    json::object log;
    log["UUID"] = 9999;
    log["text"] = text;
    log["id"] = this->id.str();
    this->addTextInternal(log, sync);
}

json::array TextLogModule::getTextLogs(){
    json::array list;
    for(auto uuid : this->textList){
        list.push_back(this->textLogs[uuid]);
    }
    return list;
}



void TextLogModule::removeText(json::value log, bool sync){
    string uuidStr = json::value_to<string>(log.get_object().at("UUID"));
    uint128_t uuid = uint128_t(uuidStr);

    if(this->textLogs.find(uuid) == this->textLogs.end()){
    return;
    }
    this->textList.erase(remove(this->textList.begin(), this->textList.end(), uuid), this->textList.end());
    this->textLogs.erase(uuid);

    json::object rmData;
    rmData["UUID"] = uuid.str();
    this->OnChange("REMOVE_TEXT", rmData);

     if( sync ){
        json::object data;
        data["textLog"] = rmData;
        this->Output("REMOVE_TEXT", data);
     }
}



void TextLogModule::updateText(json::value log, bool sync){
    string uuidStr = json::value_to<string>(log.get_object().at("UUID"));
    uint128_t uuid = uint128_t(uuidStr);
    if(this->textLogs.find(uuid) == this->textLogs.end()){
        return;
    }
    this->textLogs[uuid]["text"] = log.at("text");
    json::value updatedLog = this->getTextLog(uuid);
    this->OnChange("UPDATE_TEXT", updatedLog);
    if( sync ){
    json::object outputData;
    outputData["textLog"] = updatedLog;
       this->Output("UPDATE_TEXT" , outputData);
    }
}

void TextLogModule::addTextInternal(json::object log, bool sync){
    string uuidStr = json::value_to<string>(log.at("UUID"));
    uint128_t uuid = uint128_t(uuidStr);    
    this->textList.push_back(uuid);
    this->textLogs[uuid] = log;

    json::value updatedLog = this->getTextLog(uuid);
    this->OnChange("ADD_TEXT", updatedLog);

    if(sync){
        json::object outputData;
        outputData["textLog"];
        this->Output("ADD_TEXT" , outputData);
    }
}

void TextLogModule::clear(bool sync){
    this->textLogs.clear();
    this->textList.clear();

    this->OnChange("CLEAR", json::object());

    if(sync){
        
        this->Output("CLEAR" , json::object());
    }
}

json::value TextLogModule::getState(){
    json::object state;
    state["textLogs"] = this->getTextLogs();
    return state;
}

void TextLogModule::setState(json::value state){
    json::array logs = state.get_object().at("textLogs").get_array();
    for(auto log : logs){
        if(log.is_object()){
            this->addTextInternal(log.get_object(), false);
        }
        
    }
}

