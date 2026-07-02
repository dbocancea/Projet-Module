#include "TextLogModule.hpp"

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
    this->SetOnCommand("ADD_TEXT", [this](textLog textlog)
    {
        this->addTextInternal(textlog);
    });
    this->SetOnCommand("REMOVE_TEXT", [this](textLog textlog)
    {
        this->removeText(textlog);
    });
    this->SetOnCommand("UPDATE_TEXT", [this](textLog textlog)
    {
        this->updateText(textlog);
    });

    this->SetOnCommand("CLEAR", [this](textLog textlog)
    {
        this->clear();
    });

    
}


textLog TextLogModule::getTextLog(uint128_t textUUID){
    return this->textLogs[textUUID];
}

void TextLogModule::addText(string text, bool sync){
    textLog log;
    log.text = text;
    log.id = this->id;
    log.UUID = 9999;
    this->addTextInternal(log, sync);
}

vector<textLog> TextLogModule::getTextLogs(){
    vector<textLog> list;
    for(auto uuid : this->textList){
        list.push_back(this->textLogs[uuid]);
    }
    return list;
}



void TextLogModule::removeText(textLog log, bool sync){
    if(this->textLogs.find(log.UUID) == this->textLogs.end()){
        return;
    }

    this->textList.erase(remove(this->textList.begin(), this->textList.end(), log.UUID), this->textList.end());
    this->textLogs.erase(log.UUID);

    this->OnChange("REMOVE_TEXT", log);

     if( sync )
        this->outputFn(pair<string, textLog >{"REMOVE_TEXT" , log});
}

void TextLogModule::updateText(textLog log, bool sync){
    if(this->textLogs.find(log.UUID) == this->textLogs.end()){
        return;
    }
    this->textLogs[log.UUID].text = log.text;
    this->OnChange("UPDATE_TEXT", getTextLog(log.UUID));
     if( sync )
        this->outputFn(pair<string, textLog >{"UPDATE_TEXT" , log});
}

void TextLogModule::addTextInternal(textLog log, bool sync){
    this->textList.push_back(log.UUID);
    this->textLogs[log.UUID] = log;
    this->OnChange("ADD_TEXT", getTextLog(log.UUID));

    if( sync )
        this->outputFn(pair<string, textLog >{"ADD_TEXT" , log});
}

void TextLogModule::clear(bool sync){
    this->textLogs.clear();
    this->textList.clear();

    this->OnChange("CLEAR", {});
    textLog clear = {};

    if(sync){
        this->outputFn(pair<string, textLog >{"CLEAR" , {}});
    }
}

vector<textLog> TextLogModule::getState(){
    return this->getTextLogs();
}

void TextLogModule::setState(vector<textLog> state){
    for(auto log : state){
        this->addTextInternal(log, false);
    }
}

