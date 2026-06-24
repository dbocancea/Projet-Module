#include "GLTFModule.hpp"

GLTFModule::GLTFModule()
{
    this->type = "GLTFModule";
};

GLTFModule::GLTFModule( uint128_t UUID )
{
    this->UUID = UUID;
    this->command.push_back("SET_SCENE_GRAPH");
    this->command.push_back("SET_NODES");
    this->command.push_back("UPDATE_NODES");
    this->command.push_back("CLEAR");

    this->type = "GLTFModule";

    this->SetOnCommand("SET_NODES" , [&]( vector<Nodes> node) { this->SetNodes(node); } );
    
    this->SetOnCommand("SET_NODES" , [&]( vector<Nodes> node) { this->SetNodes(node); } );
};

void GLTFModule::SetNodes(vector<Nodes> nodes)
{
    vector<uint128_t> nodesUUID;
    for( auto node : nodes )
    {
        sceneGraph.AddNode(node);
        nodesUUID.push_back(node.UUID);
    }
    vector<Nodes> nodes = sceneGraph.NodesData(nodesUUID);
    this->OnChange("SET_NODES" , nodes);
}

void GLTFModule::UpdateNodes(vector<Nodes> nodes)
{
    vector<uint128_t> nodesUUID;
    for( auto node : nodes )
    {
        sceneGraph.UpdateNode(node);
        nodesUUID.push_back(node.UUID);
    }
    vector<Nodes> nodes = sceneGraph.NodesData(nodesUUID);
    this->OnChange("UPDATE_NODES" , nodes);


}
