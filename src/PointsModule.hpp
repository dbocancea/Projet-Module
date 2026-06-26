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
        PointsModule(uint128_t UUID);
        vector<uint128_t> getPointsUUID();
        vector<float> getPoint(uint128_t UUID);
        vector<vector<float>> getPoints(uint128_t UUID);
        void addPoints(const vector<pair<uint128_t, vector<float>>>& points, bool sync);
        void removePoints(vector<pair<uint128_t, vector<float>>>& points, bool sync);
        void updatePoints(vector<pair<uint128_t, vector<float>>>& points, bool sync);
        void clear(bool sync);
        vector<pair<uint128_t, vector<float>>> getState();
        void setState(vector<pair<uint128_t, vector<float>>> state);
};
  
#endif