#ifndef TEXTLOGMODULE_HPP
#define TEXTLOGMODULE_HPP
#include "Core/ModuleCore.hpp"


class TextLogModule : public ModuleCore
{
    private:
        uint128_t id;
        map<uint128_t, boost::json::object> textLogs;
        vector<uint128_t> textList;

        void addTextInternal(boost::json::object log, bool sync = false);
    public:
        TextLogModule();
        TextLogModule(uint128_t UUID);

        void addText(string text, bool sync = false);
        void removeText(boost::json::value log, bool sync = false);
        void updateText(boost::json::value text, bool sync = false);
        void clear(bool sync = false);

        boost::json::array getTextLogs();
        boost::json::object getTextLog(uint128_t textUUID);
        boost::json::value getState();
        void setState(boost::json::value state);
};
  
#endif