#ifndef TREE_HPP
#define TREE_HPP
#include "Core/ModuleCore.hpp"
#include<set>
using namespace boost::multiprecision;
using namespace std;

struct str_Transform {
    array<float, 3> translation ;   
    array<float, 4> rotation ; 
    array<float, 3> scale ;   
};

struct str_Nodes
{
    uint128_t UUID;
    uint128_t parent;
    set <uint128_t > children;
    Transform tran;
};


using Nodes = struct str_Nodes;
using Transform = struct str_Transform;

class SceneGraph
{   
    public:
        set<uint128_t> nodes;
        set<uint128_t> roots;
        map<uint128_t , uint128_t> parent;
        map <uint128_t , set<uint128_t>> childrens;
        map <uint128_t , Transform> transform;
        const  uint128_t ROOT_UUID = 0;
        SceneGraph();
        void AddNode(Nodes node);
        void UpdateNode(Nodes node);
};


#endif