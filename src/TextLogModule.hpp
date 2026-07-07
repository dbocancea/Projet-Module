#ifndef TEXTLOGMODULE_HPP
#define TEXTLOGMODULE_HPP
#include "Core/ModuleCore.hpp"

struct str_textLog
{
    uint128_t id;
    uint128_t UUID;
    string text;
};

using TextLog = str_textLog;

class TextLogModule : public ModuleCore
{
private:
    uint128_t id;
    map<uint128_t, TextLog> textLogs;
    vector<uint128_t> textList;
    void OnaddTextInternal(json::object log, bool sync = false);
    void addTextInternal(uint128_t uuid, TextLog t, bool sync = false);

public:
    TextLogModule();
    TextLogModule(uint128_t UUID);

    void addText(string text, bool sync = false);
    void OnremoveText(boost::json::value log);
    void OnupdateText(boost::json::value text);
    void updateText(uint128_t uuid, TextLog t, bool = false);
    void clear(bool sync = false);
    void removeText(uint128_t uuid, bool sync = false);
    boost::json::array getTextLogs();
    TextLog getTextLog(uint128_t textUUID);
    boost::json::value getState();
    void setState(boost::json::value state);
};

#endif