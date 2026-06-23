#ifndef LINEMODULE_HPP
#define LINEMODULE_HPP
#include "Core/ModuleCore.hpp"

class LineModule : public ModuleCore
{
    private:    
        vector<float> origin;
        vector<float> end;

    public:
        LineModule();
        LineModule(uint128_t UUID);
        void updateLine(vector<float> line); 


};

#endif