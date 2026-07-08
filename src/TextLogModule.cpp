#include "TextLogModule.hpp"

namespace json = boost::json;

TextLogModule::TextLogModule() : ModuleCore()
{
    this->type = "TextLogModule";
}

TextLogModule::TextLogModule(uuids::uuid UUID) : ModuleCore(UUID)
{
    cout << "TextLogModule - constructor" << endl;
    boost::uuids::random_generator gen;
    this->id = gen();
    this->type = "TextLogModule";
    this->command["addText"] = "ADD_TEXT";
    this->command["removeText"] = "REMOVE_TEXT";
    this->command["updateText"] = "UPDATE_TEXT";
    this->command["clear"] = "CLEAR";
    this->SetOnCommand(this->command["addText"], [this](json::value textlog)
                       { this->OnaddTextInternal(textlog.get_object().at("textLog").get_object()); });
    this->SetOnCommand(this->command["removeText"], [this](json::value textlog)
                       { this->OnremoveText(textlog.get_object().at("textLog")); });
    this->SetOnCommand(this->command["updateText"], [this](json::value textlog)
                       { this->OnupdateText(textlog.get_object().at("textLog")); });

    this->SetOnCommand(this->command["clear"], [this](json::value textlog)
                       { this->clear(); });
}

TextLog TextLogModule::getTextLog(uuids::uuid textUUID)
{
    return this->textLogs[textUUID];
}

void TextLogModule::OnaddTextInternal(json::object log, bool sync)
{
    string uuidStr = json::value_to<string>(log.at("UUID"));
    uuids::uuid uuid = uuids::string_generator{}(uuidStr);

    TextLog t;
    string idStr = json::value_to<string>(log.at("id"));
    uuids::uuid id = uuids::string_generator{}(idStr);
    t.id = id;
    t.UUID = uuid;
    t.text = log["text"].as_string().c_str();

    this->addTextInternal(uuid, t, sync);
}

void TextLogModule::addTextInternal(uuids::uuid uuid, TextLog t, bool sync)
{
    this->textList.push_back(uuid);
    this->textLogs[uuid] = t;

    json::object updatedLog;
    updatedLog["id"] = uuids::to_string(t.id);
    updatedLog["UUID"] = uuids::to_string(t.UUID);
    updatedLog["text"] = t.text;
    this->OnChange(this->command["addText"], updatedLog);

    if (sync)
    {
        json::object outputData;
        outputData["textLog"] = updatedLog;
        this->Output(this->command["addText"], outputData);
    }
}

void TextLogModule::addText(string text, bool sync)
{
    json::object log;
    log["UUID"] = 9999;
    log["text"] = text;
    log["id"] = uuids::to_string(this->id);
    this->OnaddTextInternal(log, sync);
}

json::array TextLogModule::getTextLogs()
{
    json::array list;
    for (auto uuid : this->textList)
    {
        json::object obj;
        obj["id"] = uuids::to_string(this->textLogs[uuid].id);
        obj["UUID"] = uuids::to_string(this->textLogs[uuid].UUID);
        obj["text"] = this->textLogs[uuid].text;
        list.push_back(obj);
    }
    return list;
}

void TextLogModule::OnremoveText(json::value log)
{
    string uuidStr = json::value_to<string>(log.get_object().at("UUID"));
    uuids::uuid uuid = uuids::string_generator{}(uuidStr);

    if (this->textLogs.find(uuid) == this->textLogs.end())
    {
        return;
    }

    this->removeText(uuid, false);
}

void TextLogModule::removeText(uuids::uuid uuid, bool sync)
{
    if (this->textLogs.find(uuid) == this->textLogs.end())
    {
        return;
    }
    this->textList.erase(remove(this->textList.begin(), this->textList.end(), uuid), this->textList.end());
    this->textLogs.erase(uuid);

    json::object rmData;
    rmData["UUID"] = uuids::to_string(uuid);
    this->OnChange(this->command["removeText"], rmData);

    if (sync)
    {
        json::object data;
        data["textLog"] = rmData;
        this->Output(this->command["removeText"], data);
    }
}

void TextLogModule::OnupdateText(json::value log)
{
    string uuidStr = json::value_to<string>(log.get_object().at("UUID"));
    uuids::uuid uuid = uuids::string_generator{}(uuidStr);
    if (this->textLogs.find(uuid) == this->textLogs.end())
    {
        return;
    }
    TextLog t;
    string idStr = json::value_to<string>(log.get_object().at("id"));
    uuids::uuid id = uuids::string_generator{}(idStr);
    t.id = id;
    t.UUID = uuid;
    t.text = log.as_object()["text"].as_string().c_str();
    this->updateText(uuid, t, false);
}

void TextLogModule::updateText(uuids::uuid uuid, TextLog t, bool sync)
{
    if (this->textLogs.find(uuid) == this->textLogs.end())
    {
        return;
    }
    this->textLogs[uuid] = t;
    json::object updatedLog;
    updatedLog["id"] = uuids::to_string(t.id);
    updatedLog["UUID"] = uuids::to_string(t.UUID);
    updatedLog["text"] = t.text;

    this->OnChange(this->command["updateText"], updatedLog);
    if (sync)
    {
        json::object outputData;
        outputData["textLog"] = updatedLog;
        this->Output(this->command["updateText"], outputData);
    }
}

void TextLogModule::clear(bool sync)
{
    this->textLogs.clear();
    this->textList.clear();

    this->OnChange(this->command["clear"], json::object());

    if (sync)
    {

        this->Output(this->command["clear"], json::object());
    }
}

json::value TextLogModule::getState()
{
    json::object state;
    state["textLogs"] = this->getTextLogs();
    return state;
}

void TextLogModule::setState(json::value state)
{
    json::array logs = state.get_object().at("textLogs").get_array();
    for (auto log : logs)
    {
        if (log.is_object())
        {
            this->OnaddTextInternal(log.get_object(), false);
        }
    }
}
