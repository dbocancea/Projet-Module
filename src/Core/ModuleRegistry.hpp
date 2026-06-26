#ifndef MODULEREGESTRY_HPP
#define MODULEREGESTRY_HPP
#include"ModuleCore.hpp"
#include <cstdlib>

class ModuleRegistry : public ModuleCore<vector<float>>
{
    private:
        map< uint128_t , ModuleCore<vector<float>>* > modules;
    public:
        const string type = "ModuleRegistry";
        ModuleRegistry();
        ModuleRegistry(  function<void (pair<string, vector<float> >) > outputFn)  ;
        void AddModule(uint128_t UUID , bool sync);
        void OnAddModule( vector<float> data );
        void RemoveModule(uint128_t UUID );
        void OnRemoveModule( function<void(vector<float>)> data );
        ModuleCore<vector<float>>* GetModule(uint128_t UUID);
};

#endif