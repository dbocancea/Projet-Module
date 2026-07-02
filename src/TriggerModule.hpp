#ifndef TRIGGERMODULE_HPP
#define TRIGGERMODULE_HPP
#include "Core/ModuleCore.hpp"
namespace json = boost::json;

class TriggerModule : public ModuleCore
{
    public:
        TriggerModule();
        TriggerModule(uint128_t UUID);

        void trigger(bool sync = false);
};
  
#endif