#include "PrimitiveModule.hpp"

PrimitiveModule::PrimitiveModule() : TransformModule(0)
{
    this->type = "PrimitiveModule";
}

PrimitiveModule::PrimitiveModule(uint128_t UUID) : TransformModule(UUID)
{
    this->type = "PrimitiveModule";
<<<<<<< HEAD
    this->SetOnCommand("UPDATE_PRIMITIVE", [this](string primitive)
    {
        this->updatePrimitive(primitive);
=======
    this->SetOnCommand("UPDATE_PRIMITIVE", [this](this->primitive)
    {
        this->updatePrimitive(this->primitive);
>>>>>>> TransformModule
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
<<<<<<< HEAD
        auto it = state.begin();
        this->TransformModule::setState(it->first);
        this->updatePrimitive(it->second);
=======
        return this->primitive;
    }

    vector<string> PrimitiveModule::getPrimitiveTypes()
    {
        return this->primitiveTypes;
    }

    void PrimitiveModule::updatePrimitive(string primitive, bool sync = false)
    {
        this->primitive = primitive;

        this->OnChange("UPDATE_PRIMITIVE", primitive);

        if(sync)
            cout << "UPDATE_PRIMITIVE " << this->primitive << endl;
    }

    map<map<string, vector<float>>, string> PrimitiveModule::getState()
    {
        return {this->getState(), this->primitive};
    }

    void PrimitiveModule::setState(map<map<string, vector<float>>, string> state)
    {
        this->setState(state);
        this->updatePrimitive(state->second);
>>>>>>> TransformModule
    }
}
