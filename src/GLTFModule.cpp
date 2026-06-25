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

    this->SetOnCommand("SET_NODES" , [&]( vector<Nodes> node) { this->SetNodes(node , 0); } );
    
    this->SetOnCommand("SET_NODES" , [&]( vector<Nodes> node) { this->SetNodes(node , 0); } );
};

void GLTFModule::SetNodes(vector<Nodes> nodes , bool sync)
{
    vector<uint128_t> nodesUUID;
    for( auto node : nodes )
    {
        sceneGraph.AddNode(node);
        nodesUUID.push_back(node.UUID);
    }
    vector<Nodes> nodesData = sceneGraph.NodesData(nodesUUID);
    this->OnChange("SET_NODES" , nodesData);

    if(sync)
        this->outputFn({"SET_NODES", nodesData});
}

void GLTFModule::UpdateNodes(vector<Nodes> nodes , bool sync)
{
    vector<uint128_t> nodesUUID;
    for( auto node : nodes )
    {
        sceneGraph.UpdateNode(node);
        nodesUUID.push_back(node.UUID);
    }
    vector<Nodes> nodesData = sceneGraph.NodesData(nodesUUID);
    this->OnChange("UPDATE_NODES" , nodesData);

    if(sync)
        this->outputFn({"UPDATE_NODES", nodesData});
}

GLTF_state GLTFModule::GetState()
{
    GLTF_state state;
    state.file = this->file;
    state.nodes = this->sceneGraph.nodes;
    return state;
}

void GLTFModule::SetState(GLTF_state state)
{
    this->UpdateFile(state.file , 0 );
    vector<uint128_t> nodeUUIDs(state.nodes.begin(), state.nodes.end());
    vector<Nodes> nodesData = sceneGraph.NodesData(nodeUUIDs);

    this->SetNodes(nodesData , 0);
}