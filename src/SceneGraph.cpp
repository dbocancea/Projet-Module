#include"SceneGraph.hpp"

SceneGraph::SceneGraph(){}

void SceneGraph::AddNode(Nodes node)
{
    this->nodes.insert(node.UUID);
    this->parent[node.UUID] = node.parent;
    
    if (this->parent.at(node.UUID) == ROOT_UUID)
        this->roots.insert(node.UUID);
    this->childrens[node.UUID] = node.children;

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