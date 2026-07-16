#include "PointsModule.hpp"

PointsModule::PointsModule()
{
    this->type = "PointsModule";

    this->points = json::object();
    this->position = json::object();
}

PointsModule::PointsModule( uuids::uuid UUID ) : ModuleCore( UUID )
{
    this->type = "PointsModule";

    this->points = json::object( );
    this->position = json::object( );

    this->SetOnCommand( "ADD_POINTS", [this](const json::value points )
    {
        this->PointsModule::onAddPoints( points );
    });

    this->SetOnCommand( "REMOVE_POINTS", [this]( const json::value points )
    {
        this->PointsModule::onRemovePoints( points );

    });


    this->SetOnCommand( "UPDATE_POINTS", [this]( const json::value points )
    {
        this->PointsModule::onUpdatePoints( points );
    });

    this->SetOnCommand( "CLEAR", [this]( const json::value fake )
    {

        this->PointsModule::onClear( );
    } );
}

vector<uuids::uuid> PointsModule::getPointsUUID( )
{
    vector<uuids::uuid> keys;
    keys.reserve( this->points.as_object( ).size( ) );
    uuids::string_generator gen;
    for( auto& kv : this->points.as_object( ) )
        keys.push_back(gen(std::string(kv.key())));
    return keys;
}

json::value PointsModule::getPoint(uuids::uuid UUID )
{
    auto& UUID_points = this->points.as_object( );
    auto it = UUID_points.find( uuids::to_string(UUID) );

    if( it != UUID_points.end( ) )
        return it->value( );

    return json::array( );
}

json::value PointsModule::getPoints( uuids::uuid UUID )
{
    return this->GetState( );
}

void PointsModule::onAddPoints( const json::value add_points, bool sync )
{
    if( !add_points.is_object( ) ) return;

    auto& obj = add_points.as_object( );

    if( !obj.contains( "points" ) || !obj.at( "points" ).is_array( ) ) return;

    json::array points_array = obj.at( "points" ).as_array( );
    json::object &inter_points =   this->points.as_object( );

    for( auto& item : points_array )
    {
        if( item.is_object( ) )
        {
            auto& pt =  item.as_object( );
            if( pt.contains( "UUID" ) && pt.contains( "position" ) )
            {
                string pt_uuid = pt.at( "UUID" ).as_string( ).c_str( );
                inter_points[ pt_uuid ] = pt.at( "position" );
            }
        }
    }

    this->addPoints( add_points, sync );
}

void PointsModule::addPoints( const json::value add_points, bool sync )
{
    this->OnChange( "ADD_POINTS", add_points );

    if( sync )
        this->Output( "ADD_POINTS", add_points );
}

void PointsModule::onRemovePoints( const json::value points_remove, bool sync )
{
    if( !points_remove.is_object( ) ) return;

    auto& obj = points_remove.as_object( );

    if( !obj.contains( "points" ) || !obj.at( "points" ).is_array( ) ) return;

    json::array points_array = obj.at( "points" ).as_array( );
    json::object &inter_points = this->points.as_object( );

    for( auto& item : points_array )
    {
        if( item.is_object( ) )
        {
            auto& pt = item.as_object( );
            if( pt.contains( "UUID" ) )
            {
                string pt_uuid = pt.at( "UUID" ).as_string( ).c_str( );
                inter_points.erase( pt_uuid ); 
            }
        }
    }

    this->removePoints( points_remove, sync );
}

void PointsModule::removePoints( const json::value points_remove, bool sync )
{
    this->OnChange( "REMOVE_POINTS", points_remove );

    if( sync )
        this->Output( "REMOVE_POINTS", points_remove );
}

void PointsModule::onUpdatePoints( const json::value points_update, bool sync )
{
    if( !points_update.is_object( ) ) return;

    auto& obj = points_update.as_object( );

    if( !obj.contains( "points" ) || !obj.at( "points" ).is_array( ) ) return;

    json::array points_array = obj.at( "points" ).as_array( );
    json::object& inter_points = this->points.as_object( );

    for( auto item : points_array )
    {
        if( item.is_object( ) )
        {
            auto& pt = item.as_object( );
            if( pt.contains( "UUID" ) && pt.contains( "position" ) )
            {
                string pt_uuid = pt.at( "UUID" ).as_string( ).c_str( );
                if( inter_points.contains( pt_uuid ) )
                {
                    inter_points[ pt_uuid ] = pt.at( "position" );
                }
            }
        }
    }

    this->updatePoints( points_update, sync );
}

void PointsModule::updatePoints( const json::value points_update, bool sync )
{
    this->OnChange( "UPDATE_POINTS", points_update );

    if( sync )
        this->Output( "UPDATE_POINTS", points_update);
}

void PointsModule::onClear( bool sync )
{
    this->points.as_object( ).clear( );

    this->clear( sync );
}

void PointsModule::clear( bool sync )
{
    this->OnChange( "CLEAR", json::object( ) );

    if( sync )
        this->Output( "CLEAR", json::object( ) );
}

json::value PointsModule::GetState( )
{
    json::array server_array;

    for( auto& key_val : this->points.as_object( ) )
    {
        json::object single_point;
        single_point[ "UUID" ] = key_val.key( );
        single_point[ "position" ] = key_val.value( );
        server_array.push_back( single_point );
    }

    json::object state;
    state[ "points" ] = server_array;

    return state;
}

void PointsModule::SetState( json::value state )
{
    this->onAddPoints( state );
}

