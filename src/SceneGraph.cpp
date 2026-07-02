#include"SceneGraph.hpp"

SceneGraph::SceneGraph(){}

void SceneGraph::AddNode(json::value node)
{
    json::object obj = node.as_object();
//UUID
    string uuid_str = obj.at("UUID").as_string().c_str();
    uint128_t uuid_n(uuid_str);
    this->nodes.insert(uuid_n);
//Parent
    uint128_t uuid_p = ROOT_UUID;
    if (obj.contains("parent")) 
        uuid_p = uint128_t(string(obj.at("parent").as_string().c_str()));
    
    this->parent[uuid_n] = uuid_p;
    if (uuid_p == ROOT_UUID)
        this->roots.insert(uuid_n);
//Child
    this->childrens[uuid_n] = {};
    if (obj.contains("children")) {
        for (const auto& v : obj.at("children").as_array()) 
        {
            string s = v.as_string().c_str();
            this->childrens[uuid_n].insert(uint128_t(s));
        }
    }
//Transform
    auto toArray3 = [](const json::array& a) -> array<float, 3> {
        return { static_cast<float>(a[0].as_double()),
                 static_cast<float>(a[1].as_double()),
                 static_cast<float>(a[2].as_double()) };
    };
    auto toArray4 = [](const json::array& a) -> array<float, 4> {
        return { static_cast<float>(a[0].as_double()),
                 static_cast<float>(a[1].as_double()),
                 static_cast<float>(a[2].as_double()),
                 static_cast<float>(a[3].as_double()) };
    };

    array<float, 3> defaultTranslation = { 0, 0, 0 };
    array<float, 4> defaultRotation    = { 0, 0, 0, 1 };
    array<float, 3> defaultScale       = { 1, 1, 1 };
    
    if (obj.contains("transform") ) 
    {
        auto& tObj = obj.at("transform").as_object();
        this->transform[uuid_n] = {
            tObj.contains("translation") ? toArray3(tObj.at("translation").as_array()) : defaultTranslation,
            tObj.contains("rotation")    ? toArray4(tObj.at("rotation").as_array())    : defaultRotation,
            tObj.contains("scale")       ? toArray3(tObj.at("scale").as_array())       : defaultScale
        };
    } 
    else 
    {
        this->transform[uuid_n] = { defaultTranslation, defaultRotation, defaultScale };
    }
}

void SceneGraph::UpdateNode(json::value node)
{
    json::object obj = node.as_object();
    string uuid_str = obj.at("UUID").as_string().c_str();
    uint128_t uuid_n(uuid_str);

    if (this->nodes.find(uuid_n) == this->nodes.end())
        return;

   

    if( obj.contains("parent") )
    {
        uuid_str = obj.at("parent").as_string().c_str();
        uint128_t uuid_p(uuid_str);
        this->parent[uuid_n] = uuid_p;
    }
        
    if( obj.contains("children") )
    {
        this->childrens[uuid_n].clear();
        for (const auto& v : obj.at("children").as_array()) 
        {
            string s = v.as_string().c_str();
            this->childrens[uuid_n].insert(uint128_t(s));
        }
    }
  
    if(obj.contains("transform"))
    {
        auto& tObj = obj.at("transform").as_object();
    
            if( tObj.contains("translation") )
            {
                json::array a = tObj["translation"].as_array() ;
                for ( int i = 0; i<a.size() ; i++ )
                    this->transform[uuid_n].translation[i] = static_cast<float>(a[i].as_double());
            } 
        
            if( tObj.contains("rotation") )
            {
                json::array a = tObj["rotation"].as_array() ;
                for ( int i = 0; i<a.size() ; i++ )
                    this->transform[uuid_n].rotation[i] = static_cast<float>(a[i].as_double());
            } 
            
            if( tObj.contains("scale") )
            {
                json::array a = tObj["scale"].as_array() ;
                for ( int i = 0; i<a.size() ; i++ )
                    this->transform[uuid_n].scale[i] = static_cast<float>(a[i].as_double());
            } 
    }
    
}

json::value SceneGraph::NodesData(vector<uint128_t> nodeUUIDs)
{   
   json::array nodes_data;
    for ( auto UUID : nodeUUIDs ) 
    {
        json::object node;
        node["UUID"] = json::string(UUID.str());
        node["parent"] = json::string(this->parent[UUID].str());

        json::array child_arr;
        for( const auto& child : this->childrens[UUID])
            child_arr.push_back( json::string (child.str()) );

        node["childrens"] = child_arr;

        node["transform"] = this->getTransform(UUID);
        
        nodes_data.push_back(node);
    }
    return nodes_data;
}

vector<uint128_t> SceneGraph::GetNodeUUIDs()
{
    return vector<uint128_t>(this->nodes.begin(), this->nodes.end());
}


json::value SceneGraph::getTransform(uint128_t UUID )
{
    json::object obj_tran;
    
    const auto& t = this->transform[UUID];
    json::array translation = { t.translation[0] , t.translation[1] , t.translation[2]};
    json::array rotation = { t.rotation[0] , t.rotation[1] , t.rotation[2] , t.rotation[3]};
    json::array scale = { t.scale[0] , t.scale[1] , t.scale[2]};
    obj_tran["translation"] = translation;
    obj_tran["rotation"] = rotation;
    obj_tran["scale"] = scale;

    return obj_tran;
}

uint128_t SceneGraph::getParent(uint128_t UUID )
{
    return this->parent[UUID];
}

set<uint128_t> SceneGraph::getChildrens(uint128_t UUID )
{
    return this->childrens[UUID];
}

void SceneGraph::clear()
{
    this->nodes.clear();
    this->childrens.clear();
    this->parent.clear();
    this->roots.clear();
}

json::value SceneGraph::getNodes()
{
    return this->NodesData(vector<uint128_t>(this->nodes.begin(), this->nodes.end()));
}