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

    this->SetOnCommand("SET_NODES" , [&]( vector<float>) { this. } )
    
};


