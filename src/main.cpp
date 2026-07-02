#include "Core/ModuleCore.hpp"
#include "TextModule.hpp"

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

    onchange = false;
    module.updateText("trying sync", true);
    if(module.getText() == "trying sync" && onchange && output){
        cout << "updateText: passed, onchange & output" << endl;
    }
    else cout << "updateText: test failed" << endl;



    return 0;
}