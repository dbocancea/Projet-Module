#ifndef MODULECORE_HPP
#define MODULECORE_HPP

#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <boost/json.hpp>
#include <memory>
using namespace boost::multiprecision;
using namespace std;
namespace json = boost::json;


class ModuleCore
{
protected:
    
    vector<string> command;
    uint128_t UUID;
    function<void(json::value)> callback;
    map<string, vector<function<void(json::value)>>> commandCallBack;
    map<string, vector<function<void(json::value)>>> changeCallBack;
   
public:
    
     function<void(json::value)> outputFn;
    string type;
    ModuleCore() ;
    ModuleCore(uint128_t UUID) ;

    void SetOnCommand(const string& command, function<void(json::value)> callback) ;
    void OnCommand(const string& command, json::value data) ;

    void SetOnChange(const string& command, function<void(json::value)> callback) ;
    void OnChange(const string& command, json::value data) ;
    virtual json::value Encode(const string& command, json::value data);
    void SetOutputFn( function<void(json::value)> outputFn );
    virtual void SetState(json::value state);
    virtual json::value GetState();
    uint128_t GetUUID();
    void Output(const string& command, json::value data);
    virtual ~ModuleCore() = default;
};



#endif