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
        std::map<std::string, std::vector <float>> commands;
        std::array<float, TRANSLATION_SIZE> translation {};
        std::array<float, ROTATION_SIZE> rotation {};
        std::array<float, SCALE_SIZE> scale {};
    public:
        TransformModule(uint128_t UUID);
        void updateTransform(vector<float> transform, bool sync);
        std::tuple<std::array<float, TRANSLATION_SIZE>, std::array<float, ROTATION_SIZE>, std::array<float, SCALE_SIZE>> getTransform();
        map<string, vector<float>> getState();
        void setState(map<string, vector<float>> state);
};
  
#endif
