#ifndef POINTSMODULE_HPP
#define POINTSMODULE_HPP
#include "Core/ModuleCore.hpp"

class PointsModule : public ModuleCore
{
    protected:
        json::value position;
        json::value points;
    public:
        PointsModule( );
        PointsModule( uuids::uuid UUID );
        vector<uuids::uuid> getPointsUUID( );
        json::value getPoint( uuids::uuid UUID );
        json::value getPoints( uuids::uuid UUID );
        void onAddPoints( const json::value add_points, bool sync = false );
        void addPoints( const json::value add_points, bool sync = false );
        void onRemovePoints( const json::value points_remove, bool sync = false );
        void removePoints( const json::value points_remove, bool sync = false );
        void onUpdatePoints( const json::value points_update, bool sync = false );
        void updatePoints( const json::value points_update, bool sync = false );
        void onClear( bool sync = false );
        void clear( bool sync = false );
        json::value getState( );
        void setState( json::value state );
};
  
#endif