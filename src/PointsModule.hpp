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
        uint128_t getPointsUUID();
        vector<float> getPoint(uint128_t UUID);
        vector<vector<float>> getPoints(uint128_t UUID);
        void addPoints(const vector<float>& points, bool sync);
        void removePoints(vector<float>& points, bool sync);
        void updatePoints(vector<float>& points, bool sync);
        void clear(bool sync);
        map<string, vector<float>> getState();
        void setState(map<string, vector<float>> state);
};
  
#endif
