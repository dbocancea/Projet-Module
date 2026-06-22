#include"ModuleRegistry.hpp"

ModuleRegistry::ModuleRegistry(){}

ModuleRegistry::ModuleRegistry(  function<void (pair<string, vector<float> >) > outputFn ) : ModuleCore(0)
{   
    string cmd1 = "ADD_MODULE";

    string cmd2 = "REMOVE_MODULE";

    this->command.push_back(cmd1);
    this->command.push_back(cmd2);
    this->outputFn = outputFn;
    this->SetOnCommand(cmd1, [&](vector<float> data) {this->OnAddModule(data);} );

    this->SetOnCommand(cmd2, [&](vector<float> data) {this->outputFn({"REMOVE_MODULE" , data});} );
}

void ModuleRegistry::OnAddModule( vector<float> data )
{
    float type = data[0];
    string type_str = "";
    if ( type == 0.0 )
        type_str = "ModuleCore";
    else if( type == 1.0 ) 
        type_str = "CameraModule";
    uint128_t UUID = uint128_t(data[1]);
    cout << "Add module " << type << " " + type_str + " " << UUID << endl;  
}

void ModuleRegistry::AddModule( uint128_t UUID , bool sync )
{
    auto it = this->modules.find(UUID);
    if( it != this->modules.end() )
    {
        cout << "Exists already " << endl;
        return;
    }
    ModuleCore* module = new ModuleCore(UUID);
    module->SetOutputFn(this->outputFn);

    modules.insert( {UUID , module} );
    if (sync)
        this->outputFn( pair< string , vector<float> > {"ADD_MODULE", {0. , 1. , 2.}});
}

void ModuleRegistry::RemoveModule(uint128_t UUID )
{
    auto it = this->modules.find(UUID);
    if( it == this->modules.end() )
    {
        cout << UUID <<" module don't existe " << endl;
        return;
    }
    
    ModuleCore* delete_mod = it->second;

    delete delete_mod;

    modules.erase(it);
    
}

ModuleCore* ModuleRegistry::GetModule(uint128_t UUID)
{
    auto it = modules.find(UUID);
    if ( it != modules.end() )
        return it->second;
    cerr << "UUID doesn't exists " << endl;
    return nullptr;
}
/*
int main()
{   
    ModuleRegistry modMan( [&] (pair< string, vector<float> >  outputFn ) 
    {std::cout << "OutputFn called with command: " << outputFn.first << std::endl;} );
    modMan.AddModule(123 , 0);
    modMan.GetModule(1111);
    modMan.AddModule(321 , 0);
    ModuleCore* newmod = modMan.GetModule(321);
    cout << "UUID " << newmod->GetUUID() << endl;
    modMan.RemoveModule(123);
    modMan.RemoveModule(321);
    modMan.GetModule(321);
    return 0;
}
    */