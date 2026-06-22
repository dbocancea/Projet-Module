#include "ModuleCore.hpp"
ModuleCore::ModuleCore() {}
ModuleCore::ModuleCore(uint128_t UUID)
{   
    string cmd = "SET_STATE";
    this->command.push_back(cmd);
    this->type = "ModulCore";
    this->UUID = UUID;
    this->callback = ([&]( vector<float>) {});
    this->SetOnCommand(cmd, this->callback );
}

void ModuleCore::SetOnCommand(string command, function<void(vector<float>)> callback)
{
    auto it = this->commandCallBack.find(command);
    if (it == this->commandCallBack.end())
        this->commandCallBack.insert( {command, vector < function < void (vector<float> ) > >{} } );
    commandCallBack[command].push_back(callback);
}

void ModuleCore::OnCommand(string command, vector<float> data)
{
    auto it = this->commandCallBack.find(command);
    if (it != this->commandCallBack.end())
        for (auto callback_temp : it->second)
            callback_temp(data);
    else
        cout << this->UUID << " has no member " << endl;
}

void ModuleCore::SetOutputFn( function<void (pair<string, vector<float> >) > outputFn )
{
    this->outputFn = outputFn;
}

uint128_t ModuleCore::GetUUID()
{
    return this->UUID;
}

void add(vector<float> tab)
{
    float sum = 0;
    for (auto it : tab)
        sum += it;
    cout << "Sum = " << sum << endl;
}

void sub(vector<float> tab)
{
    float sub = 0;
    for (auto it : tab)
        sub -= it;
    cout << "Sub = " << sub << endl;
}

void mul(vector<float> tab)
{
    float mul = 1;
    for (auto it : tab)
        mul *= it;
    cout << "Mul = " << mul << endl;
}

int main()
{ 

    ModuleCore mod = ModuleCore( 1234 );
     ModuleCore mod1 = ModuleCore( 1234 );
     mod.SetOnCommand("TEST", [&]( vector<float> v) {
         cout << v.size() << endl;
     });
         mod.SetOnCommand("TEST", [&]( ::vector<float> v) {
         cout << "test2 " << v.size() << endl;
     });
             mod.SetOnCommand("COMMAND", [&]( ::vector<float> v) {
         cout << "command " << v.size() << endl;
     });
     mod.OnCommand( "TEST", vector<float> { 1.0, 2.0, 3.0 });
     mod.OnCommand( "COMMAND", vector<float> { 1.0, 2.0, 3.0 });

     mod.SetOutputFn( [&](pair<string, vector<float>> message){ 
         mod1.OnCommand( message.first, message.second );
     } );

     mod1.SetOutputFn( [&](pair<string, vector<float>> message){ 
         mod.OnCommand( message.first, message.second );
     } );
     vector <float> tab{1.,2.,3.};

     
    mod1.outputFn(pair<string , vector<float>> ("TEST" , tab) );
    
    return 0;
}
    
    