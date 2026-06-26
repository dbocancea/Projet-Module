#ifndef SCALARMODULE_HPP
#define SCALARMODULE_HPP
#include "Core/ModuleCore.hpp"

class ScalarModule : public ModuleCore<int>
{   
    protected:
        int value=0;
    public:
        ScalarModule();
        ScalarModule(uint128_t UUID) ;
        void UpdateValue(int value , bool sync);
        void SetState(int value);
        int GetState();
};
  
#endif