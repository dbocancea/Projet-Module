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
        LineModule(uuids::uuid UUID);
        void UpdateLine( vector<float> origin , vector<float> end , bool sync = false );
        void OnUpdateLine(boost::json::value line);
        boost::json::value getLine();
        boost::json::value GetState() override;
        void SetState(boost::json::value state) override;
        
};

#endif