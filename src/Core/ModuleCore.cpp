#include "ModuleCore.hpp"
template <typename T>
ModuleCore<T>::ModuleCore() {}
template <typename T>
ModuleCore<T>::ModuleCore(uint128_t UUID)
{   
    string cmd = "SET_STATE";
    this->command.push_back(cmd);
    this->type = "ModuleCore";
    this->UUID = UUID;
    this->callback = ([&]( vector<float>) {});
    this->SetOnCommand(cmd, this->callback );
}
template <typename T>
void ModuleCore<T>::SetOnCommand(string command, function<void(T)> callback)
{
    auto it = this->commandCallBack.find(command);
    if (it == this->commandCallBack.end())
        this->commandCallBack.insert( {command, vector < function < void (T ) > >{} } );
    commandCallBack[command].push_back(callback);
}
template <typename T>
void ModuleCore<T>::OnCommand(string command, T data)
{
    auto it = this->commandCallBack.find(command);
    if (it != this->commandCallBack.end())
        for (auto callback_temp : it->second)
            callback_temp(data);
    else
        cout << this->UUID << " has no member " << endl;
}
template <typename T>
void ModuleCore<T>::SetOnChange(string command, function<void(T)> callback)
{
    auto it = this->changeCallBack.find(command);
    if (it == this->changeCallBack.end())
        this->changeCallBack.insert( {command, vector < function < void (T ) > >{} } );
    changeCallBack[command].push_back(callback);
}

template <typename T>
void ModuleCore<T>::OnChange(string command, T data)
{
    auto it = this->changeCallBack.find(command);
    if (it != this->changeCallBack.end())
        for (auto callback_temp : it->second)
            callback_temp(data);
    else
        cout << this->UUID << " has no member " << endl;
}
template <typename T>
void ModuleCore<T>::SetOutputFn( function<void (pair<string, T >) > outputFn )
{
    this->outputFn = outputFn;
}
template <typename T>
uint128_t ModuleCore<T>::GetUUID()
{
    return this->UUID;
}
template <typename T>
void add(T tab)
{
    float sum = 0;
    for (auto it : tab)
        sum += it;
    cout << "Sum = " << sum << endl;
}
template <typename T>
void sub(T tab)
{
    float sub = 0;
    for (auto it : tab)
        sub -= it;
    cout << "Sub = " << sub << endl;
}
template <typename T>
void mul(T tab)
{
    float mul = 1;
    for (auto it : tab)
        mul *= it;
    cout << "Mul = " << mul << endl;
}
