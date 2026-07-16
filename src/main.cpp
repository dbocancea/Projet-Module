#include "Core/ModuleRegistry.hpp"
#include "Core/ModuleTypes.hpp"

int main()
{   
    uuids::random_generator gen;

    uuids::uuid fileModuuid1 = gen();
    uuids::uuid fileModuuid2 = gen();

    uuids::uuid cameraModuleuuid3 = gen( );
    uuids::uuid cameraModuleuuid4 = gen( );

    uuids::uuid pointsModuleuuid1 = gen( );
    uuids::uuid pointsModuleuuid2 = gen( );

    CameraModule cam1 { cameraModuleuuid3 };
    CameraModule cam2 ( cameraModuleuuid4 );

    uuids::uuid imUUID = gen( );

    ImageModule im1 { imUUID };

    cout << "Type: " << im1.type << "\n";

    cout << "Command: " << im1.GetCommand( )[ "setImage" ] << "\n";

    json::object image_input;

    image_input[ "image" ] = "https://img.magnific.com/photos-gratuite/gros-plan-beau-papillon-textures-interessantes-fleur-petale-orange_181624-7640.jpg?semt=ais_hybrid&w=740&q=80";

    json::object trans_data;

    trans_data[ "translation" ] = { 0.0, 0.0, 0.0 };
    trans_data[ "rotation" ] = { 0.0, 0.0, 0.0, 0.0 };
    trans_data[ "scale" ] = { 0.0, 0.0, 0.0 };

    image_input[ "transform" ] = trans_data;

    im1.SetState( image_input );

    json::value res = im1.GetState( );

    cout << res << "\n";

    cout << imUUID << "\n";

    cout << "Camera type: " << cam1.type << "\n";

    cout << "Camera state: " << cam2.GetState() << "\n";

    ModuleRegistry modules ( []( json::value val ) 
    {
        string json_str = json::serialize( val );
        cout << json_str << endl;
    } );

    modules.AddModule( "PointsModule", pointsModuleuuid1, true );
    modules.AddModule( "PointsModule", pointsModuleuuid2, true );

    auto pointsModule1 = static_pointer_cast<PointsModule>( modules.modules[pointsModuleuuid1] );
    auto pointsModule2 = static_pointer_cast<PointsModule>( modules.modules[pointsModuleuuid2] );

    pointsModule1->SetOutputFn( [ &pointsModule2 ]( json::value payload ) 
    {
        pointsModule2->input( payload );
    } );

    pointsModule2->SetOutputFn( [ &pointsModule1 ]( json::value payload ) 
    {
        pointsModule1->input( payload );
    } );

    string pt1 = uuids::to_string( gen( ) );
    string pt2 = uuids::to_string( gen( ) );

    json::object add_points;
    json::array pt_array;
    json::object p1;
    json::object p2;

    p1[ "UUID" ] = pt1;
    p1[ "position" ] = { 1., 2., 3. };

    p2[ "UUID" ] = pt2;
    p2[ "position" ] = { 2.2, 9.1, 3.3 };

    pt_array.push_back( p1 );
    pt_array.push_back( p2 );

    add_points[ "points" ] = pt_array;

    pointsModule2->onAddPoints( add_points, true );

    json::object update_points;
    json::array update_array;
    json::object pt_update;

    pt_update[ "UUID" ] = pt1;
    pt_update[ "position" ] = {15., 19., 33. };

    update_array.push_back( pt_update );
    update_points[ "points" ] = update_array;

    pointsModule2->onAddPoints( update_points, true );

    if( pointsModule1->GetState( ) == pointsModule2->GetState( ) )
    {
        cout << "Sync ok" << endl;
    }
    else
    {
        cout << "Sync not ok" << endl;
    }

    json::value val1 = modules.modules[ pointsModuleuuid1 ]->GetState( );
    modules.outputFn( val1 );

    json::value val2 = modules.modules[ pointsModuleuuid2 ]->GetState( );
    modules.outputFn( val2 );

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