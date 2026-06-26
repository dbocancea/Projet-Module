#ifndef LINEMODULE_HPP
#define LINEMODULE_HPP
#include "Core/ModuleCore.hpp"

class LineModule : public ModuleCore<pair<vector<float>, vector<float>>>
{
    private:    
        vector<float> origin;
        vector<float> end;

    public:
        LineModule();
        LineModule(uint128_t UUID);
        void updateLine(pair<vector<float>, vector<float>> line); 
        pair<vector<float>, vector<float>> getLine();
        pair<vector<float>, vector<float>> getState();
        void setState(pair<vector<float>, vector<float>> state);

};

#endif