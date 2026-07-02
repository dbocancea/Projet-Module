#ifndef TRIGGERMODULE_HPP
#define TRIGGERMODULE_HPP
#include "Core/ModuleCore.hpp"

class TriggerModule : public ModuleCore<bool>
{
    public:
        TriggerModule();
        TriggerModule(uint128_t UUID);

        void trigger(bool sync = false);
};
  
#endif