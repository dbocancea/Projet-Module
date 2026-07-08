#ifndef MODULECORE_HPP
#define MODULECORE_HPP

#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/string_generator.hpp>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <boost/json.hpp>
#include <memory>

namespace uuids = boost::uuids;
using namespace std;
namespace json = boost::json;


class ModuleCore
{
protected:
    
    map<string , string> command;
    uuids::uuid UUID;
    function<void(json::value)> callback;
    map<string, vector<function<void(json::value)>>> commandCallBack;
    map<string, vector<function<void(json::value)>>> changeCallBack;
   
public:
    
     function<void(json::value)> outputFn;
    string type;
    ModuleCore() ;
    ModuleCore(uuids::uuid UUID) ;

    void SetOnCommand(const string& command, function<void(json::value)> callback) ;
    void OnCommand(const string& command, json::value data) ;

    void SetOnChange(const string& command, function<void(json::value)> callback) ;
    void OnChange(const string& command, json::value data) ;
    virtual json::value Encode(const string& command, json::value data);
    void SetOutputFn( function<void(json::value)> outputFn );
    virtual void SetState(json::value state);
    virtual json::value GetState();
    uuids::uuid GetUUID();
    void Output(const string& command, json::value data);
    string GetType();
    map<string , string> GetCommand();
    json::value outputState();
    void input(json::value payload);
    virtual ~ModuleCore() = default;

};



#endif