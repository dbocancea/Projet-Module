#ifndef TEXTMODULE_HPP
#define TEXTMODULE_HPP
#include "Core/ModuleCore.hpp"

class TextModule : public ModuleCore<string>
{
    protected:
        string text;
    public:
        TextModule();
        TextModule(uint128_t UUID);
        void UpdateText(string text; bool sync);
        string GetText();
        string GetState();
        void SetState(string state);
};
  
#endif