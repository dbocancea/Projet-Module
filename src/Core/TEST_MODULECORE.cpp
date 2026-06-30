#include "ModuleCore.hpp"

int main()
{
    ModuleCore<vector<float>> mod1( 1222 );
    ModuleCore<vector<float>> mod2( 1222 );

    mod1.SetOnCommand("ADD", [&](vector<float> data)
    {
        cout << "ADD complete in" << data.size() << endl;

        mod1.OnChange("ADD_EVENT", data);
    });

    mod2.SetOnCommand("ADD", [&](vector<float> data)
    {
        cout << "ADD complete. Size: " << data.size() << endl;

        mod2.OnChange("ADD_EVENT", data);
    });

    mod1.SetOnChange("ADD_EVENT", [&](vector<float> data)
    {
        cout << "We added command ADD in mod1 " << endl;
    });

    mod2.SetOnChange("ADD_EVENT", [&](vector<float> data)
    {
        cout << "We added command ADD in mod2 " << endl;
    });

    mod1.SetOutputFn([&](pair<string, vector<float>> outPutData)
    {
        mod2.OnCommand(outPutData.first, outPutData.second);
    });

    mod2.SetOutputFn([&](pair<string, vector<float>> outPutData)
    {
        mod1.OnCommand(outPutData.first, outPutData.second);
    });

    vector<float> data = {1.f, 2.f, 0.f};

    cout << "test" << endl;
    
    if(mod1.outputFn)
        mod1.outputFn({"ADD", data});

    if(mod2.outputFn)
        mod2.outputFn({"ADD", data});

    cout << "Mod1 " << mod1.GetUUID() << endl;
    cout << "Mod2 " << mod2.GetUUID() << endl;

    bool msg_delivred{false};
    string cmd{};
    vector<float>msg_data{};

    mod1.SetOutputFn([&](pair<string, vector<float>> outPutFn)
    {
        msg_delivred = true;
        cmd = outPutFn.first;
        msg_data = outPutFn.second;
    });

    vector<float> testData = {1.f, 3.f};

    if(mod1.outputFn)
    {
        mod1.outputFn({"Test", testData});
    }
    if(msg_delivred && cmd == "Test" && msg_data.size() == 2)
    {
        cout << "Good" << endl;
    }
    else
    {
        cout << "Bad" << endl;
    }

    return 0;
}