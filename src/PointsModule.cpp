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
        this->PointsModule::addPoints(points);
    });

    this->SetOnCommand("REMOVE_POINTS", [this](const vector<pair<uint128_t, vector<float>>>& points)
    {
        this->PointsModule::removePoints(points);
    });

    this->SetOnCommand("UPDATE_POINTS", [this](const vector<pair<uint128_t, vector<float>>>& points)
    {
        this->PointsModule::updatePoints(points);
    });

    this->SetOnCommand("CLEAR", [this](const vector<pair<uint128_t, vector<float>>>& fake)
    {
        this->PointsModule::clear();
    });
}

vector<uint128_t> PointsModule::getPointsUUID()
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

vector<vector<float>> PointsModule::getPoints(uint128_t UUID)
{
    vector<vector<float>> tous_points;
    tous_points.reserve(this->points.size());
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
    this->OnCommand("ADD_POINTS ", points);

    if(sync)
        cout << "ADD_POINTS" << points.size() << endl;
}

void PointsModule::removePoints(const vector<pair<uint128_t, vector<float>>>& points, bool sync)
{
    for(auto &[uuid, position] : points)
    {
        this->points.erase(uuid);
    }

    this->OnCommand("REMOVE_COMMANDS", points);

    if(sync)
        cout << "REMOVE_POINTS " << points.size() << endl;
}

void PointsModule::updatePoints(const vector<pair<uint128_t, vector<float>>>& points, bool sync)
{
    for(auto &[uuid, position] : points)
    {
        auto it = this->points.find(uuid);
        if(it != this->points.end())
        {
            vector<float> positionCopy(3, 0.0f);

            for(size_t i = 0; i < position.size() && i < 3; ++i)
            {
                positionCopy[i] = position[i];
            }
            it->second = positionCopy;
        }
    }

    if(sync)
    {
        cout << "UPDATE_POINTS " << endl;
    }
}

void PointsModule::clear(bool sync)
{
    this->points.clear();

    this->OnCommand("CLEAR", vector<pair<uint128_t, vector<float>>>());

    if(sync)
        cout << "CLEAR " << endl;
}

map<uint128_t, vector<float>> PointsModule::getState()
{
    return this->points;
}

void PointsModule::setState(vector<pair<uint128_t, vector<float>>> state)
{
    this->addPoints(state);
}
