#ifndef GLTFMODULE_HPP
#define GLTFMODULE_HPP
#include "FileModule.hpp"
#include "SceneGraph.hpp"



class GLTFModule : public  ModuleCore<vector<Nodes>>
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
};
  
#endif