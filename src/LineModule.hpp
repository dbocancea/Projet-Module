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
        //void updateLine(pair<vector<float>, vector<float>> line);
        void updateLine(boost::json::value line, bool sync = false);
        boost::json::value getLine();
        boost::json::value getState();
        void setState(boost::json::value state);
        
};

#endif