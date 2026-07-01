#ifndef MESHMODULE_HPP
#define MESHMODULE_HPP

#include "FileModule.hpp"

class MeshModule : public FileModule
{
    public:
        MeshModule();
        MeshModule(uint128_t UUID);
        json::value getState();
        void SetState( json::value state );
};


#endif