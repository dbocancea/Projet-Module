#include "PointsModule.hpp"

PointsModule::PointsModule()
{
    this->type = "PointsModule";
}

PointsModule::PointsModule(uint128_t UUID) : ModuleCore(UUID)
{
    this->type = "PointsModule";
    this->SetOnCommand("ADD_POINTS", [this](const vector<float>& points)
    {
        this->addPoints(points, false);
    });
}
