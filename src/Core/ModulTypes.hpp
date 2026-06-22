#ifndef MODULTYPES_HPP
#define MODULTYPES_HPP
#include "ModuleCore.hpp"
#include "ModuleRegistry.hpp"

using FnModulTypes = function<ModuleCore*()>;

const map<string ,FnModulTypes > ModulTypes = {
    {"ModuleCore" , [](){ return new ModuleCore(); }  },
    {"ModuleRegestry" , [](){ return new ModuleRegistry(); }  }
};


#endif