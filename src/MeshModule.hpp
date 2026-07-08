#ifndef MESHMODULE_HPP
#define MESHMODULE_HPP

#include "FileModule.hpp"

class MeshModule : public FileModule
{
    public:
        MeshModule();
        MeshModule(uuids::uuid UUID);
        json::value getState();
        void SetState( json::value state );
};


#endif