#ifndef GLTFMODULE_HPP
#define GLTFMODULE_HPP
#include "FileModule.hpp"
#include "SceneGraph.hpp"

struct strGLTF_state
{
    File file;
    set<uint128_t> nodes;
};

using GLTF_state = strGLTF_state;

class GLTFModule : public  FileModule<vector<Nodes>>
{   
    protected:
        FileModule fileHandler;
        const uint128_t root_UUID = 0;
        SceneGraph sceneGraph;
    public:
        GLTFModule();
        GLTFModule(uint128_t UUID);
        void SetNodes(vector<Nodes> nodes );
        void UpdateNodes(vector<Nodes> nodes );
        GLTF_state GetState();
        void SetState(GLTF_state state);
};  
  
#endif