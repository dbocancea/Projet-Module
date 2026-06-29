#include "PrimitiveModule.hpp"

PrimitiveModule::PrimitiveModule()
{
    this->type = "PrimitiveModule";
}

PrimitiveModule::PrimitiveModule(uint128_t UUID) : TransformModule(UUID)
{
    this->type = "PrimitiveModule";
    this->SetOnCommand("UPDATE_PRIMITIVE", [this](this->primitive, false)
    {
        this->updatePrimitive(this->primitive, false);
    });

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
    }
}
