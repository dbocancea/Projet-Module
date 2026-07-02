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

<<<<<<< HEAD
    this->SetOnCommand( "ADD_POINTS", [this]( const json::value points )
    {
        this->PointsModule::addPoints( points );
    } );
=======
    this->points = json::object();
    this->position = json::object();

    this->SetOnCommand( "ADD_POINTS", [this](const json::value points )
    {
        this->PointsModule::addPoints( points );
    });
>>>>>>> origin/PointsModule

    this->SetOnCommand( "REMOVE_POINTS", [this]( const json::value points )
    {
        this->PointsModule::removePoints( points );
<<<<<<< HEAD
    } );
=======
    });
>>>>>>> origin/PointsModule

    this->SetOnCommand( "UPDATE_POINTS", [this]( const json::value points )
    {
        this->PointsModule::updatePoints( points );
<<<<<<< HEAD
    } );
=======
    });
>>>>>>> origin/PointsModule

    this->SetOnCommand( "CLEAR", [this]( const json::value fake )
    {
        this->PointsModule::clear();
    } );
}

vector<uint128_t> PointsModule::getPointsUUID()
{
    vector<uint128_t> keys;
<<<<<<< HEAD
    keys.reserve( points.size() );
    for( auto& it : points )
        keys.push_back( it.first );
    return keys;
}

vector<float> PointsModule::getPoint( uint128_t UUID )
{
    auto it = points.find( UUID );

    if( it != points.end() )
        return it->second;
=======
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
>>>>>>> origin/PointsModule

    return json::array();
}

<<<<<<< HEAD
vector<vector<float>> PointsModule::getPoints( uint128_t UUID )
{
    vector<vector<float>> tous_points;
    tous_points.reserve( this->points.size() );
    for( auto &[uuid, pos] : points )
        tous_points.push_back( pos );

    return tous_points;
}

void PointsModule::addPoints( const json::value points, bool sync = false )
{
    if( !points.is_object() ) return;

    for( auto& key_value : points.as_object() )
    {
        uint128_t uuid( string( key_value.key() ) );
        if( key_value.value().is_array() )
        {
            auto& liste = key_value.value().as_array();
            vector<float> position_copy( 3, 0.f );

            for( size_t i = 0; i < liste.size() && i < 3; ++i )
                position_copy[i] = liste[i].to_number<float>();
            
            this->points[uuid] = position_copy;
        }
    }

    this->OnChange( "ADD_POINTS", points );

    if(sync)
        cout << "ADD_POINTS" << points.as_object().size() << endl;  
}

void PointsModule::removePoints( const json::value points, bool sync )
{
    if( !points.is_object() ) return;

    for( auto& key_value : points.as_object() )
    {
        uint128_t uuid( string( key_value.key() ) );
        this->points.erase( uuid );
    }
    this->OnChange( "REMOVE_COMMANDS", points );

    if( sync )
        cout << "REMOVE_POINTS " << points  << endl;
}

void PointsModule::updatePoints( const json::value points, bool sync )
{
    if( !points.is_object() ) return;

    for( auto& key_value : points.as_object() )
    {
        uint128_t uuid( string ( key_value.key() ) );

        auto it = this->points.find( uuid );
        if( it != this->points.end() )
        {
            auto& liste = key_value.value().as_array();
            vector<float> positionCopy(3, 0.0f);

            for( size_t i = 0; i < position.size() && i < 3; ++i )
            {
                positionCopy[i] = liste[i].to_number<float>();
            }
            it->second = positionCopy;
        }
    }

    if(sync)
    {
        cout << "UPDATE_POINTS " << points << endl;
    }
}

void PointsModule::clear( bool sync )
{
    this->points.clear();

    this->OnChange( "CLEAR", json::value() );

    if( sync )
        cout << "CLEAR " << endl;
}

=======
json::value PointsModule::getPoints( uint128_t UUID )
{
    this->points;
}

void PointsModule::addPoints( const json::value add_points, bool sync = false )
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

>>>>>>> origin/PointsModule
json::value PointsModule::getState()
{
    json::object obj;

    for( auto& [uuid, pos] : this->points )
    {
        json::array liste;
        for( float val : pos )
            liste.push_back( val );
        
        obj[uuid.str()] = liste;
    }

    return obj;
}

void PointsModule::setState(json::value state)
{
    this->addPoints(state);
}
