#ifndef TEXTLOGMODULE_HPP
#define TEXTLOGMODULE_HPP
#include "Core/ModuleCore.hpp"

struct textLog {
    uint128_t UUID;
    string text; 
    uint128_t id;
};

class TextLogModule : public ModuleCore<textLog>
{
    private:
        uint128_t id;
        map<uint128_t, textLog> textLogs;
        vector<uint128_t> textList;

        void addTextInternal(textLog log, bool sync = false);
    public:
        TextLogModule();
        TextLogModule(uint128_t UUID);

        void addText(string text, bool sync = false);
        void removeText(textLog log, bool sync = false);
        void updateText(textLog text, bool sync = false);
        void clear(bool sync = false);

        vector<textLog> getTextLogs();
        textLog getTextLog(uint128_t textUUID);
        vector<textLog> getState();
        void setState(vector<textLog> state);
};
  
#endif