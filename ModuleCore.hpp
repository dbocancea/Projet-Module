#ifndef MODULECORE_HPP
#define MODULECORE_HPP

#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace boost::multiprecision;
using namespace std;


class ModuleCore
{
protected:
    
    vector<string> command;
    uint128_t UUID;
    function<void(vector<float>)> callback;
    map<string, vector<function<void(vector<float>)>>> commandCallBack;

public:
function<void (pair<string, vector<float> >) > outputFn;
    string type;
    ModuleCore() ;
    ModuleCore(uint128_t UUID) ;
    void SetOnCommand(string command, function<void(vector<float>)> callback) ;
    void OnCommand(string command, vector<float> data) ;
    void SetOutputFn( function<void (pair<string, vector<float> >) > outputFn );
    void SetState();
    void GetState();
    uint128_t GetUUID();
};



#endif