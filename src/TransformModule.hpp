#ifndef TRANSFORMMODULE_HHP
#define TRANSFORMMODULE_HHP

#define TRANSLATION_SIZE 3
#define ROTATION_SIZE 4
#define SCALE_SIZE 3

#include "Core/ModuleCore.hpp"
#include <array>
#include <tuple>
template<typename T>
class TransformModule : public ModuleCore<vector<float>>
{
    protected:
        map<string, vector <float>> commands;
        array<float, TRANSLATION_SIZE> translation {};
        array<float, ROTATION_SIZE> rotation {};
        array<float, SCALE_SIZE> scale {};
    public:
        TransformModule(uint128_t UUID);
        void updateTransform(vector<float> transform, bool sync);
        tuple<array<float, TRANSLATION_SIZE>, array<float, ROTATION_SIZE>, array<float, SCALE_SIZE>> getTransform();
        map<string, vector<float>> getState();
        void setState(map<string, vector<float>> state);
};
  
#endif