#include "PrimitiveModule.hpp"

PrimitiveModule::PrimitiveModule() : TransformModule(0)
{
    this->type = "PrimitiveModule";
}

PrimitiveModule::PrimitiveModule(uint128_t UUID) : TransformModule(UUID)
{
    this->type = "PrimitiveModule";
    this->SetOnCommand("UPDATE_PRIMITIVE", [this](string primitive)
    {
        this->updatePrimitive(primitive);
    });
}

string PrimitiveModule::getPrimitive()
{
    return this->primitive;
}

vector<string> PrimitiveModule::getPrimitiveTypes()
{
    return this->primitiveTypes;
}

void PrimitiveModule::updatePrimitive(string primitive, bool sync)
{
    this->primitive = primitive;

    this->OnChange("UPDATE_PRIMITIVE", this->primitive);

    if(sync)
        cout << "UPDATE_PRIMITIVE " << this->primitive << endl;
}

map<string, map<string, vector<float>>> PrimitiveModule::getState()
{
    map<string, map<string, vector<float>>> res {};
    auto transState = this->TransformModule::getState();
    res[this->TransformModule::getState()] = this->primitive;
    return res;
}

void PrimitiveModule::setState(map<map<string, vector<float>>, string> state)
{
    if(!state.empty())
    {
        auto it = state.begin();
        this->TransformModule::setState(it->first);
        this->updatePrimitive(it->second);
    }
}
