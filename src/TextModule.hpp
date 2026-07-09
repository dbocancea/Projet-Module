#ifndef TEXTMODULE_HPP
#define TEXTMODULE_HPP
#include "Core/ModuleCore.hpp"

class TextModule : public ModuleCore
{
    private:
        string text;
    public:
        TextModule();
        TextModule(uuids::uuid UUID);

        void updateText(string text, bool sync = false);
        string getText();
        boost::json::value GetState() override;
        void SetState(boost::json::value state) override;

};
  
#endif