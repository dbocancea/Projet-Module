#include "PointsModule.hpp"

PointsModule::PointsModule()
{
    this->type = "PointsModule";

    this->points = json::object();
    this->position = json::object();
}

PointsModule::PointsModule( uint128_t UUID ) : ModuleCore( UUID )
{
    this->type = "PointsModule";

    this->points = json::object();
    this->position = json::object();

    this->SetOnCommand( "ADD_POINTS", [this](const json::value points )
    {
        this->PointsModule::addPoints( points );
    });

    this->SetOnCommand( "REMOVE_POINTS", [this]( const json::value points )
    {
        this->PointsModule::removePoints( points );
    });

    this->SetOnCommand( "UPDATE_POINTS", [this]( const json::value points )
    {
        this->PointsModule::updatePoints( points );
    });

    this->SetOnCommand( "CLEAR", [this]( const json::value fake )
    {
        this->PointsModule::clear();
    });
}

vector<uint128_t> PointsModule::getPointsUUID()
{
    vector<uint128_t> keys;
    keys.reserve( this->points.as_object().size() );
    for( auto& kv : this->points.as_object() )
        keys.push_back( uint128_t ( kv.key_c_str() ) );
    return keys;
}

json::value PointsModule::getPoint( uint128_t UUID )
{
    auto& UUID_points = this->points.as_object();
    auto it = UUID_points.find( UUID.str() );

    if( it != UUID_points.end() )
        return it->value();

    return json::array();
}

json::value PointsModule::getPoints( uint128_t UUID )
{
    this->points;
}

void PointsModule::addPoints( const json::value add_points, bool sync )
{
    if( !add_points.is_object() ) return;

    json::object& UUID_points = this->points.as_object();

    for( auto& kv : add_points.as_object() )
    {
        if( kv.value().is_array() )
            UUID_points[kv.key()] =  kv.value();
    }
    this->OnChange( "ADD_POINTS ", add_points );

    if( sync )
        this->Output( "ADD_POINTS ", add_points );
}

void PointsModule::removePoints( const json::value points_remove, bool sync )
{
    if( !points_remove.is_object() ) return;

    json::object& UUID_points = this->points.as_object();

    for( auto& kv : points_remove.as_object() )
        UUID_points.erase( kv.key() );

    this->OnChange( "REMOVE_POINTS", points_remove );

    if( sync )
        this->Output( "REMOVE_POINTS", points_remove );
}

void PointsModule::updatePoints( const json::value points_update, bool sync )
{
    if( !points_update.is_object() ) return;

    json::object& UUID_points = this->points.as_object();
    for(auto& kv : points_update.as_object() )
    {
        if( UUID_points.contains( kv.key() ) )
            UUID_points[kv.key()] = kv.value();
    }

    this->OnChange( "UPDATE_POINTS", points_update);

    if( sync )
        this->Output( "REMOVE_COMMANDS", points_update );
}

void PointsModule::clear( bool sync )
{
    this->points.as_object().clear();;

    this->OnCommand( "CLEAR", json::object() );

    if( sync )
        this->Output( "CLEAR", json::object() );
}

json::value PointsModule::getState()
{
    return this->points;
}

void PointsModule::setState(json::value state)
{
    this->addPoints(state);
}