#include "PointsModule.hpp"
#include "Core/ModuleRegistry.hpp"

int main( )
{
    uuids::random_generator gen;
    uuids::uuid UUID1 = gen( );
    uuids::uuid UUID2 = gen( );

    ModuleRegistry modules ( []( json::value val ) 
    {
        string json_str = json::serialize( val );
        cout << json_str << endl;
    } );

    modules.AddModule( "PointsModule", UUID1, true );
    modules.AddModule( "PointsModule", UUID2, true );

    auto pointsModule1 = static_pointer_cast<PointsModule>( modules.modules[UUID1] );
    auto pointsModule2 = static_pointer_cast<PointsModule>( modules.modules[UUID2] );

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

    json::object new_points;

    new_points[ pt1 ] = { 1., 2., 3. };
    new_points[ pt2 ] = { 2.2, 9.1, 3.3 };

    pointsModule1->onAddPoints( new_points, true );

    json::object update_points;
    update_points[ pt1 ] = { 13., 17., 20. };

    pointsModule2->onUpdatePoints( update_points, true );

    if( pointsModule1->GetState( ) == pointsModule2->GetState( ) )
    {
        cout << "Sync ok" << endl;
    }
    else
    {
        cout << "Sync not ok" << endl;
    }

    json::value val1 = modules.modules[ UUID1 ]->GetState( );
    modules.outputFn( val1 );

    json::value val2 = modules.modules[ UUID2 ]->GetState( );
    modules.outputFn( val2 );

    return 0;
}