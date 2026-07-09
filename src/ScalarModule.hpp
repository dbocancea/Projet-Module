#ifndef SCALARMODULE_HPP
#define SCALARMODULE_HPP
#include "Core/ModuleCore.hpp"

class ScalarModule : public ModuleCore
{   
    protected:
        int value=0;
    public:
        ScalarModule();
        ScalarModule(uuids::uuid UUID) ;
        void UpdateValue(int  val , bool sync = false);
        void OnUpdateValue(json::value value);
        void SetState(json::value value) override;
        json::value GetState() override;
        int GetValue();
};
  
#endif