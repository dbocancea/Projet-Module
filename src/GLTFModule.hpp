// #ifndef GLTFMODULE_HPP
// #define GLTFMODULE_HPP
// #include "FileModule.hpp"
// #include "SceneGraph.hpp"

// struct strGLTF_state
// {
//     json::object file;
//     set<uint128_t> nodes;
// };

// class GLTFModule : public  FileModule
// {   
//     protected:
//         const uint128_t root_UUID = 0;
//         SceneGraph sceneGraph;
//     public:
//         GLTFModule();
//         GLTFModule(uint128_t UUID);
//         void SetNodes(json::value nodes , bool sync = false);
//         void UpdateNodes(json::value nodes , bool sync = false);
//         vector<uint128_t> GetNodesUUIDs();
//         json::value GetState() override;
//         void SetState(json::value state) override;
//         json::value nodeTransform(uint128_t UUID);
//         json::value nodes();
// };  
  
// #endif