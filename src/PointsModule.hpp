#ifndef POINTSMODULE_HPP
#define POINTSMODULE_HPP
#include "Core/ModuleCore.hpp"

class PointsModule : public ModuleCore
{
    protected:
        vector<float> position;
        map<uint128_t, vector<float>> points;
    public:
        PointsModule();
        PointsModule( uint128_t UUID );
        vector<uint128_t> getPointsUUID();
        vector<float> getPoint( uint128_t UUID );
        vector<vector<float>> getPoints( uint128_t UUID );
        void addPoints( const json::value points, bool sync = false );
        void removePoints( const json::value points, bool sync = false );
        void updatePoints( const json::value points, bool sync = false );
        void clear( bool sync = false );
        json::value getState();
        void setState( json::value state );
};
  
#endif