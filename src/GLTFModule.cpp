#include "GLTFModule.hpp"

GLTFModule::GLTFModule()
{
    this->type = "GLTFModule";
};

GLTFModule::GLTFModule( uint128_t UUID ) : FileModule(UUID)
{
    this->command.push_back("SET_SCENE_GRAPH");
    this->command.push_back("SET_NODES");
    this->command.push_back("UPDATE_NODES");
    this->command.push_back("CLEAR");

    this->type = "GLTFModule";

    this->SetOnCommand("SET_NODES" , [this]( json::value data) { 
        json::object obj = data.as_object();
        this->SetNodes(obj.at("nodes")); } );
    
    this->SetOnCommand("UPDATE_NODES" , [this]( json::value data) { 
        json::object obj = data.as_object();
        this->UpdateNodes(obj.at("nodes")); } );
};

void GLTFModule::SetNodes(json::value nodes , bool sync)
{

    json::array ar_nodes = nodes.as_array();

    vector<uint128_t> nodesUUID;
    for( auto node : ar_nodes )
    {
        sceneGraph.AddNode(node);
        string str_uuid = node.as_object().at("UUID").as_string().c_str();
        uint128_t uuid(str_uuid);
        nodesUUID.push_back(uuid);
    }

    json::value nodesData = sceneGraph.NodesData(nodesUUID);
    this->OnChange("SET_NODES" , nodesData);

    if(sync)
    {
        json::object payload;
        payload["nodes"] = nodesData;
        this->Output("SET_NODES" , payload);
    }

}

void GLTFModule::UpdateNodes(json::value nodes , bool sync)
{
    vector<uint128_t> nodesUUID;
    json::array ar_nodes = nodes.as_array();
    for( auto node : ar_nodes )
    {
        sceneGraph.UpdateNode(node);
        string str_uuid = node.as_object().at("UUID").as_string().c_str();
        uint128_t uuid(str_uuid);
        nodesUUID.push_back(uuid);
    }
     json::value nodesData = sceneGraph.NodesData(nodesUUID);
    this->OnChange("UPDATE_NODES" , nodesData);

    if(sync)
    {
        json::object payload;
        payload["nodes"] = nodesData;
        this->Output("UPDATE_NODES", payload);
    }
        
}

json::value GLTFModule::GetState()
{
    json::object state = FileModule::GetState().as_object();
    json::array nodesArr;
    for (const auto& uuid : this->sceneGraph.nodes)
        nodesArr.push_back(json::string(uuid.str()));
    state["nodes"] = nodesArr;
    return state;
}

void GLTFModule::SetState(json::value state)
{
   FileModule::SetState(state);

   this->SetNodes(state.as_object().at("nodes"));
}

vector<uint128_t> GLTFModule::GetNodesUUIDs()
{
    return this->sceneGraph.GetNodeUUIDs();
}

json::value GLTFModule::nodeTransform(uint128_t UUID)
{
    return this->sceneGraph.getTransform(UUID);
}

json::value GLTFModule::nodes()
{
    return this->sceneGraph.getNodes();
}