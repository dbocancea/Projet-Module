#ifndef GLTFMODULE_HPP
#define GLTFMODULE_HPP
#include "FileModule.hpp"
#include "SceneGraph.hpp"

struct strGLTF_state
{
    json::object file;
    set<uint128_t> nodes;
};

class GLTFModule : public  FileModule
{   
    protected:
        FileModule fileHandler;
        const uint128_t root_UUID = 0;
        SceneGraph sceneGraph;
    public:
        GLTFModule();
        GLTFModule(uint128_t UUID);
        void SetNodes(vector<Nodes> nodes , bool sync);
        void UpdateNodes(vector<Nodes> nodes , bool sync);
        GLTF_state GetState();
        void SetState(GLTF_state state);
};  
  
#endif