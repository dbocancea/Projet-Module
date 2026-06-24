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


template <typename T >
class ModuleCore
{
protected:
    
    vector<string> command;
    uint128_t UUID;
    function<void(T)> callback;
    map<string, vector<function<void(T)>>> commandCallBack;
    map<string, vector<function<void(T)>>> changeCallBack;
public:
function<void (pair<string, vector<float> >) > outputFn;
    string type;
    ModuleCore() ;
    ModuleCore(uint128_t UUID) ;
    void SetOnCommand(string command, function<void(T)> callback) ;
    void OnCommand(string command, T data) ;
    void SetOnChange(string command, function<void(T)> callback) ;
    
    void OnChange(string command, T data) ;
    void SetOutputFn( function<void (pair<string, T >) > outputFn );
    void SetState();
    void GetState();
    uint128_t GetUUID();
};



#endif