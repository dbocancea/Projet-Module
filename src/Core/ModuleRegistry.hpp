#ifndef MODULEREGESTRY_HPP
#define MODULEREGESTRY_HPP
#include"ModuleCore.hpp"
#include"ModuleTypes.hpp"
#include <cstdlib>

class ModuleRegistry : public ModuleCore
{
    private:
        
    public:
    map< uuids::uuid , shared_ptr<ModuleCore> > modules;
        ModuleRegistry();
        ModuleRegistry( function<void(json::value)> outputFn)  ;
        void AddModule( string type ,uuids::uuid UUID , bool sync = false);
        void OnAddModule( json::value data );
        void RemoveModule(uuids::uuid UUID , bool sync = false);
        void OnRemoveModule( json::value data );
        shared_ptr<ModuleCore> GetModule(uuids::uuid UUID);
        void SetState(json::value state) override;
        json::value GetState() override;
};

#endif