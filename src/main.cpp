#include "Core/ModuleCore.hpp"
#include "TextModule.hpp"
#include "TextLogModule.hpp"
int main()
{
    TextModule module(123);
    if (module.getText() == "") {
        cout << "get text: nice" << endl; 
    }
    else cout << "get text: not nice";


    bool onchange = false;
    module.SetOnChange("UPDATE_TEXT", [&](json::value data){
        onchange = true;
        cout << "onchange callback: " << data << endl;
    });

    bool output = false;
    module.SetOutputFn([&](json::value text){
        output = true;
        cout << "output callback: " << text << endl;
    });

    module.updateText("test");
    if(module.getText() == "test" && onchange && !output){
        cout << "updateText: passed, onchange, no output" << endl;
    }
    else cout << "updateText: test failed" << endl;
#include "TextModule.hpp"
    onchange = false;
    module.updateText("trying sync", true);
    if(module.getText() == "trying sync" && onchange && output){
        cout << "updateText: passed, onchange & output" << endl;
    }
    else cout << "updateText: test failed" << endl;

    json::object stateTest;
    stateTest["text"] = "State 1";
    module.setState(stateTest);
    json::value state = module.getState();
    if(state.as_object().at("text").as_string() == "State 1") cout << "state get, set passed" << endl;
    else cout << "state test failed";


    json::object command;
    command["text"] = "command 1";

    module.OnCommand("UPDATE_TEXT", command);
    if(module.getText() == "command 1") cout << "test on command passed" << endl;
    else cout << "oncommand test failed";


    cout << "--- TextLogModule test: ---" << endl;

    TextLogModule tmodule(44);
    
    
    return 0;
}