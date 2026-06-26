#ifndef VECTOR3MODULE_HPP
#define VECTOR3MODULE_HPP
#include "Core/ModuleCore.hpp"

class Vector3Module : public ModuleCore<array<int, 3>>
{
    protected:
        array<int, 3> vector;
    public: 
        Vector3Module();
        Vector3Module(uint128_t UUID);
        void UpdateVector( array<int, 3> vector , bool sync);
        array<int, 3> GetVector();
        array<int, 3> GetState();
        void SetState( array<int, 3> vector);
};
   
#endif