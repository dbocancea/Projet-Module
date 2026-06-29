#ifndef PRIMITIVEMODULE_HPP
#define PRIMITIVEMODULE_HPP
#include "TransformModule.hpp"

class PrimitiveModule : public ModuleCore<string>
{
    protected:
        string sphere = "sphere";
        string box = "box";

        vector<string> primitiveTypes = {sphere, box};

        string primitive = primitiveTypes[0];
    public:
        PrimitiveModule();
        PrimitiveModule(uint128_t UUID);
        string getPrimitive();
        vector<string> getPrimitiveTypes();
        void updatePrimitive(string primitive, bool sync);
        map<map<string, vector<float>>, string> getState();
        void setState(map<map<string, vector<float>>, string> state);
};
  
#endif