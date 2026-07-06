#ifndef MODULEREGESTRY_HPP
#define MODULEREGESTRY_HPP
#include"ModuleCore.hpp"
#include"ModuleTypes.hpp"
#include <cstdlib>

class ModuleRegistry : public ModuleCore
{
    private:
        map< uint128_t , shared_ptr<ModuleCore> > modules;
    public:
        ModuleRegistry();
        ModuleRegistry( function<void(json::value)> outputFn)  ;
        void AddModule( string type ,uint128_t UUID , bool sync = false);
        void OnAddModule( json::value data );
        void RemoveModule(uint128_t UUID , bool sync = false);
        void OnRemoveModule( json::value data );
        shared_ptr<ModuleCore> GetModule(uint128_t UUID);
        void SetState(json::value state) override;

        json::value GetState() override;
};

#endif