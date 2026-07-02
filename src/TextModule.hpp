#ifndef TEXTMODULE_HPP
#define TEXTMODULE_HPP
#include "Core/ModuleCore.hpp"

class TextModule : public ModuleCore
{
    private:
        string text;
    public:
        TextModule();
        TextModule(uint128_t UUID);

        void updateText(string text, bool sync = false);
        string getText();
        boost::json::value getState();
        void setState(boost::json::value state);

};
  
#endif