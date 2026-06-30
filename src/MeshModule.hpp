#ifndef MESHMODULE_HPP
#define MESHMODULE_HPP

#include "FileModule.hpp"

class MeshModule : public FileModule<File>
{
    public:
        MeshModule();
        MeshModule(uint128_t UUID);
        File getState();
        void SetState( File f );
};


#endif