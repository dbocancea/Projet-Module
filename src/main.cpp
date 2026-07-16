#include "Core/ModuleRegistry.hpp"
#include "Core/ModuleTypes.hpp"

int main()
{   
    uuids::random_generator gen;

    uuids::uuid fileModuuid1 = gen();
    uuids::uuid fileModuuid2 = gen();

    uuids::uuid cameraModuuid3 = gen( );
    uuids::uuid cameraModuuid4 = gen( );

    CameraModule cam1 { cameraModuuid3 };
    CameraModule cam2 ( cameraModuuid3 );

    // cout << UUID1 << "\n";

    cout << "Camera type: " << cam1.type << "\n";
    cout << "Camera state " << cam2.GetState() << "\n";

    ModuleRegistry modules([](json::value val){string json_str = boost::json::serialize(val); cout << json_str<< endl;});
    modules.AddModule("FileModule" , fileModuuid1, 1);
  
    modules.AddModule("FileModule" , fileModuuid2 , 1);
    auto fileModule1 = static_pointer_cast<FileModule>(modules.modules[fileModuuid1]);
    fileModule1->UpdateFile("text" , "string" , "1, 1 ,1" , 1);
    
    auto fileModule2 = static_pointer_cast<FileModule>(modules.modules[fileModuuid2]);
    fileModule2->UpdateFile("text", "string", "1, 1, 1", true); 

    fileModule1->SetOutputFn([&fileModule2](json::value payload) {
    fileModule2->input(payload);
    });

    fileModule2->SetOutputFn([&fileModule1](json::value payload) {
    fileModule1->input(payload);
    });

     

    if (fileModule1->GetState() == fileModule2->GetState())
        cout << "Sync automatique OK" << endl;
    
    json::value valF1 = modules.modules[fileModuuid1]->GetState();
    json::value valF2 = modules.modules[fileModuuid2]->GetState();
    modules.outputFn(valF1);
    modules.outputFn(valF2);

    return 0;
}