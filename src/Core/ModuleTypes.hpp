#ifndef MODULETYPES_HPP
#define MODULETYPES_HPP
#include "ModuleCore.hpp"
#include "ModuleRegistry.hpp"
#include "../CameraModule.hpp"
#include "../FileModule.hpp"
#include "../GLTFModule.hpp"
#include "../LineModule.hpp"
#include "../PointsModule.hpp"
#include "../PrimitiveModule.hpp"
#include "../ScalarModule.hpp"
#include "../TextLogModule.hpp"
#include "../TextModule.hpp"
#include "../TransformModule.hpp"
#include "../TriggerModule.hpp"
#include "../Vector3Module.hpp"

using FnModuleTypes = function<ModuleCore*()>;

const map<string ,FnModuleTypes > ModulTypes = {
    {"ModuleCore" , [](){ return new ModuleCore(); }  },
    {"ModuleRegestry" , [](){ return new ModuleRegistry(); }  },
    {"CameraModule" , [](){ return new CameraModule(); }  },
    {"FileModule" , [](){ return new FileModule(); }  },
    {"GLTFModule" , [](){ return new GLTFModule(); }  },
    {"LineModule" , [](){ return new LineModule(); }  },
    {"PointsModule" , [](){ return new PointsModule(); }  },
    {"PrimitiveModule" , [](){ return new PrimitiveModule(); }  },
    {"ScalarModule" , [](){ return new ScalarModule(); }  },
    {"TextLogModule" , [](){ return new TextLogModule(); }  },
    {"TextModule" , [](){ return new TextModule(); }  },
    {"TransformModule" , [](){ return new TransformModule(); }  },
    {"TriggerModule" , [](){ return new TriggerModule(); }  },
    {"Vector3Module" , [](){ return new Vector3Module(); }  }
};


#endif