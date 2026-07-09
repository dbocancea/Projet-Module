//#ifndef SCENEGRAPH_HPP
//#define SCENEGRAPH_HPP
//#include "Core/ModuleCore.hpp"
//#include<set>
//using namespace boost::multiprecision;
//using namespace std;
//
//struct str_Transform {
//    array<float, 3> translation ;   
//    array<float, 4> rotation ; 
//    array<float, 3> scale ;   
//};
//
//using Transform = struct str_Transform;
//
//class SceneGraph
//{   
//    public:
//        set<uint128_t> nodes;
//        set<uint128_t> roots;
//        map<uint128_t , uint128_t> parent;
//        map <uint128_t , set<uint128_t>> childrens;
//        map <uint128_t , Transform> transform;
//        const  uint128_t ROOT_UUID = 0;
//        SceneGraph();
//        void AddNode(json::value node);
//        void UpdateNode(json::value node);
//        json::value NodesData(vector<uint128_t> nodeUUIDs);
//        vector<uint128_t> GetNodeUUIDs();
//        json::value getTransform(uint128_t UUID );
//        uint128_t getParent(uint128_t UUID );
//        set<uint128_t> getChildrens(uint128_t UUID );
//        void clear();
//        json::value getNodes();
//};
//
//
//#endif