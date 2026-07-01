#ifndef TRANSFORMMODULE_HHP
#define TRANSFORMMODULE_HHP

#define TRANSLATION_SIZE 3
#define ROTATION_SIZE 4
#define SCALE_SIZE 3

#include "Core/ModuleCore.hpp"
#include <array>
#include <tuple>

class TransformModule : public ModuleCore
{
    protected:
        map<string, vector <float>> commands;
        array<float, TRANSLATION_SIZE> translation {};
        array<float, ROTATION_SIZE> rotation {};
        array<float, SCALE_SIZE> scale {};
    public:
        TransformModule();
        TransformModule(uint128_t UUID);
        void updateTransform(json::value transform, bool sync = false);
        tuple<array<float, TRANSLATION_SIZE>, array<float, ROTATION_SIZE>, array<float, SCALE_SIZE>> getTransform();
        json::value getState();
        void setState(json::value state);
};

#endif