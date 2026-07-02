#ifndef SCALARMODULE_HPP
#define SCALARMODULE_HPP
#include "Core/ModuleCore.hpp"

class ScalarModule : public ModuleCore
{   
    protected:
        int value=0;
    public:
        ScalarModule();
        ScalarModule(uint128_t UUID) ;
        void UpdateValue(json::value data , bool sync = false);
        void SetState(json::value value) override;
        json::value GetState() override;
        int GetValue();
};
  
#endif