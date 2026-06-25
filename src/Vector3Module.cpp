#include "Vector3Module.hpp"

Vector3Module::Vector3Module()
{
    this->type = "Vector3Module";
}

Vector3Module::Vector3Module(uint128_t UUID) : ModuleCore(UUID)
{
    cout << "Vector3Module - constructor" << endl;
    this->type = "Vector3Module";
    this->command.push_back("UPDATE_VECTOR");

    this->SetOnCommand("UPDATE_VECTOR", [&](array<int, 3> vector)
                       { this->UpdateVector(vector, 0); });
}

void Vector3Module::UpdateVector(array<int, 3> vector, bool sync)
{
    cout << "Vector3Module - updateVector" << endl;

    for (int i = 0; i < vector.size(); i++)
        this->vector[i] = vector[i];
    this->OnChange("UPDATE_VECTOR", this->vector);

    if (sync)
        this->outputFn({"UPDATE_VECTOR", vector});
}

array<int, 3> Vector3Module::GetVector()
{
    return this->vector;
}

array<int, 3> Vector3Module::GetState()
{
    return this->vector;
}
void Vector3Module::SetState( array<int, 3> vector)
{
    this->UpdateVector(vector , 0);
}