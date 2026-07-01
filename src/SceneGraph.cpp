#include"SceneGraph.hpp"

SceneGraph::SceneGraph(){}

void SceneGraph::AddNode(json::value node)
{
    json::object obj = node.as_object();

    string uuid_str = obj.at("UUID").as_string().c_str();
    uint128_t uuid_n(uuid_str);
    this->nodes.insert(uuid_n);
//
    uuid_str = obj.at("parent").as_string().c_str();
    uint128_t uuid_p(uuid_str);

    this->parent[uuid_n] = uuid_p;
//

   // this->nodes.insert(node.UUID);
  //  this->parent[node.UUID] = node.parent;
    
    if (this->parent.at(uuid_n) == ROOT_UUID)
        this->roots.insert(uuid_n);

    map<uint128_t , set<uint128_t>> uuid_c = json::value_to<map<uint128_t , set<uint128_t>>>(obj.at("children"));

    this->childrens[uuid_n] = uuid_c;

    uuid_str = obj.at("parent").as_string().c_str();
    uint128_t uuid_p(uuid_str);

    this->transform[node.UUID] = node.tran;
}

void SceneGraph::UpdateNode(Nodes node)
{
    if (this->nodes.find(node.UUID) == this->nodes.end())
        return;
    if (node.parent)
        this->parent[node.UUID] = node.parent;
    if( !node.children.empty() )
        this->childrens[node.UUID] = node.children;
  
    for( int i = 0; i < this->transform[node.UUID].translation.size() ; i++)
        this->transform[node.UUID].translation[i] = node.tran.translation[i];
    for( int i = 0; i < this->transform[node.UUID].rotation.size() ; i++)
        this->transform[node.UUID].rotation[i] = node.tran.rotation[i];
    for( int i = 0; i < this->transform[node.UUID].scale.size() ; i++)
        this->transform[node.UUID].scale[i] = node.tran.scale[i];
    
}

vector<Nodes> SceneGraph::NodesData(vector<uint128_t> nodeUUIDs)
{   
    vector<Nodes> nodes_data;
    for ( auto UUID : nodeUUIDs ) 
    {
        nodes_data.push_back({UUID , this->parent[UUID] , this->childrens[UUID] , this->transform[UUID]});
    }
    return nodes_data;
}