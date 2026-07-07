#include "Core/ModuleRegistry.hpp"
#include "Core/ModuleTypes.hpp"
int main()
{
    ModuleRegistry modules([](json::value val){string json_str = boost::json::serialize(val); cout << json_str<< endl;});
    modules.AddModule("FileModule" , 123 , 1);
  
    modules.AddModule("FileModule" , 1 , 1);
    auto fileModule1 = static_pointer_cast<FileModule>(modules.modules[123]);
    fileModule1->UpdateFile("text" , "string" , "1, 1 ,1" , 1);
    
    auto fileModule2 = static_pointer_cast<FileModule>(modules.modules[1]);
    fileModule1->SetOutputFn([&fileModule2](json::value payload) {
    fileModule2->input(payload);
    });
    fileModule1->UpdateFile("text", "string", "1, 1, 1", true);  

    if (fileModule1->GetState() == fileModule2->GetState())
        cout << "Sync automatique OK" << endl;
    
    json::value valF1 = modules.modules[123]->GetState();
    json::value valF2 = modules.modules[1]->GetState();
    modules.outputFn(valF1);
    modules.outputFn(valF2);
    return 0;
}