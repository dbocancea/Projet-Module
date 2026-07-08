#include "Core/ModuleRegistry.hpp"
#include "Core/ModuleTypes.hpp"
int main()
{   
    uuids::random_generator gen;
    uuids::uuid uuid1 = gen();
    uuids::uuid uuid2 = gen();
    ModuleRegistry modules([](json::value val){string json_str = boost::json::serialize(val); cout << json_str<< endl;});
    modules.AddModule("FileModule" , uuid1, 1);
  
    modules.AddModule("FileModule" , uuid2 , 1);
    auto fileModule1 = static_pointer_cast<FileModule>(modules.modules[uuid1]);
    fileModule1->UpdateFile("text" , "string" , "1, 1 ,1" , 1);
    
    auto fileModule2 = static_pointer_cast<FileModule>(modules.modules[uuid2]);
    fileModule2->UpdateFile("text", "string", "1, 1, 1", true); 

    fileModule1->SetOutputFn([&fileModule2](json::value payload) {
    fileModule2->input(payload);
    });

    fileModule2->SetOutputFn([&fileModule1](json::value payload) {
    fileModule1->input(payload);
    });

     

    if (fileModule1->GetState() == fileModule2->GetState())
        cout << "Sync automatique OK" << endl;
    
    json::value valF1 = modules.modules[uuid1]->GetState();
    json::value valF2 = modules.modules[uuid2]->GetState();
    modules.outputFn(valF1);
    modules.outputFn(valF2);
    return 0;
}