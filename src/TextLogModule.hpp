#ifndef TEXTLOGMODULE_HPP
#define TEXTLOGMODULE_HPP
#include "Core/ModuleCore.hpp"

struct str_textLog
{
    uuids::uuid id;
    uuids::uuid UUID;
    string text;
};

using TextLog = str_textLog;

class TextLogModule : public ModuleCore
{
private:
    uuids::uuid id;
    map<uuids::uuid, TextLog> textLogs;
    vector<uuids::uuid> textList;
    void OnaddTextInternal(json::object log, bool sync = false);
    void addTextInternal(uuids::uuid uuid, TextLog t, bool sync = false);

public:
    TextLogModule();
    TextLogModule(uuids::uuid UUID);

    void addText(string text, bool sync = false);
    void OnremoveText(boost::json::value log);
    void OnupdateText(boost::json::value text);
    void updateText(uuids::uuid uuid, TextLog t, bool = false);
    void clear(bool sync = false);
    void removeText(uuids::uuid uuid, bool sync = false);
    boost::json::array getTextLogs();
    TextLog getTextLog(uuids::uuid textUUID);
    boost::json::value getState();
    void setState(boost::json::value state);
};

#endif