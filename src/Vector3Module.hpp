#ifndef VECTOR3MODULE_HPP
#define VECTOR3MODULE_HPP
#include "Core/ModuleCore.hpp"

class Vector3Module : public ModuleCore
{
    protected:
        array<int, 3> vector;
    public: 
        Vector3Module();
        Vector3Module(uint128_t UUID);
        void UpdateVector( json::value vector , bool sync = false);
        array<int, 3> GetVector();
        json::value GetState() override;
        void SetState(  json::value vector) override;
};
   
#endif