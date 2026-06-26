#include "Core/ModuleCore.hpp"

int main()
{
	ModuleCore mod = ModulTypes["ModuleCore"];

	cout << mod->type << endl;

	return 0;
}