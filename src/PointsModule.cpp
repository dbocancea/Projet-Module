#include "PointsModule.hpp"

PointsModule::PointsModule()
{
    this->type = "PointsModule";
}

PointsModule::PointsModule(uint128_t UUID) : ModuleCore(UUID)
{
    this->type = "PointsModule";

    this->SetOnCommand("ADD_POINTS", [this](const vector<pair<uint128_t, vector<float>>>& points)
    {
        this->addPoints(points, false);
    });

    this->SetOnCommand("REMOVE_POINTS", [this](const vector<pair<uint128_t, vector<float>>>& points)
    {
        this->removePoints(points, false);
    });

    this->SetOnCommand("UPDATE_POINTS", [this](const vector<pair<uint128_t, vector<float>>>& points)
    {
        this->updatePoints(points, false);
    });

    this->SetOnCommand("CLEAR", [this]()
    {
        this->clear(false);
    });
}

vector<uint128_t> PointsModule::getPointsUUID();
{
    vector<uint128_t> keys;
    keys.reserve(points.size());
    for(auto& it : points)
        keys.push_back(it.first);
    return keys;
}

vector<float> PointsModule::getPoint(uint128_t UUID)
{
    auto it = points.find(UUID);

    if(it != points.end())
        return it->second;

        return {};
}

vector<vector<float>> getPoints(uint128_t UUID)
{
    vector<vector<float>> tous_points;
    tous_points.reserve(points.size());
    for(auto &[uuid, pos] : points)
        tous_points.push_back(pos);

    return tous_points;
}

void PointsModule::addPoints(const vector<pair<uint128_t, vector<float>>>& points, bool sync)
{
    for(auto& [uuid, position] : points)
    {
        vector<float> position_copy (3, 0.0f);
        for(size_t i = 0; i < position_copy.size() && i < 3; ++i)
        {
            position_copy[i] = position[i];
        }

        this->points[uuid] = position_copy;
    }
    this->OnChange("ADD_POINTS ", points);

    if(sync)
        cout << "ADD_POINTS" << points.size() << endl;
}

void PointsModule::removePoints(vector<pair<uint128_t, vector<float>>>& points, bool sync)
{
    for(auto &[uuid, position] : points)
    {
        this->points[uuid].erase();
    }

    this->OnChange("REMOVE_COMMANDS", points);

    if(sync)
        cout << "REMOVE_POINTS " << points.size() << endl;
}

void updatePoints(vector<pair<uint128_t, vector<float>>>& points, bool sync)
{
    for(auto &[uuid, position] : points)
    {
        auto it = this->points.find(uuid);
        if(it != this->points.end())
        {
            vector<float> positionCopy(3, 0.0f);

            for(size_t i = 0; i < position.size() && i < 3; ++i)
            {
                positionCopy[i] = position;
            }
        }

        it->second = positionCopy;
    }

    if(sync)
    {
        cout << "UPDATE_POINTS " << points << endl;
    }
}

void clear(bool sync)
{
    this->points.clear();

    this->OnChange("CLEAR", points);

    if(sync)
        cout << "CLEAR " << points << endl;
}

vector<pair<uint128_t, vector<float>>> PointsModule::getState()
{
    return this->points;
}

void setState(vector<pair<uint128_t, vector<float>>> state)
{
    addPoints(points, false);
}
