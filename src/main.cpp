#include "Core/ModuleTypes.hpp"

int main()
{
	uint128_t UUID = 123;
	void* rawPtr = ModulTypes.at("ModuleCore")(&UUID);

    auto* mod = static_cast<ModuleCore*>(rawPtr);

    cout << mod->type << endl;

    delete mod;
    return 0;
}