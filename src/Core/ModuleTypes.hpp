#ifndef MODULETYPES_HPP
#define MODULETYPES_HPP
#include "ModuleCore.hpp"
#include "../CameraModule.hpp"
#include "../FileModule.hpp"
#include "../LineModule.hpp"
#include "../PointsModule.hpp"
#include "../PrimitiveModule.hpp"
#include "../ScalarModule.hpp"
#include "../TextLogModule.hpp"
#include "../TextModule.hpp"
#include "../TransformModule.hpp"
#include "../TriggerModule.hpp"
#include "../Vector3Module.hpp"
#include "../ImageModule.hpp"
#include "../MeshModule.hpp"



using FnModuleTypes = void*(*)(void*);

const map<string ,FnModuleTypes > ModuleTypes = {
    {"ModuleCore" ,     [](void* arg) -> void* { return new ModuleCore(*static_cast<uuids::uuid*>(arg)); }  },
    {"CameraModule" ,   [](void* arg) -> void* { return new CameraModule(*static_cast<uuids::uuid*>(arg)); }  },
    {"FileModule" ,     [](void* arg) -> void* { return new FileModule(*static_cast<uuids::uuid*>(arg)); }  },
    {"LineModule" ,     [](void* arg) -> void* { return new LineModule(*static_cast<uuids::uuid*>(arg)); }  },
    {"PointsModule" ,   [](void* arg) -> void* { return new PointsModule(*static_cast<uuids::uuid*>(arg)); }  },
    {"PrimitiveModule" ,[](void* arg) -> void* { return new PrimitiveModule(*static_cast<uuids::uuid*>(arg)); }  },
    {"ScalarModule" ,   [](void* arg) -> void* { return new ScalarModule(*static_cast<uuids::uuid*>(arg)); }  },
    {"TextLogModule" ,  [](void* arg) -> void* { return new TextLogModule(*static_cast<uuids::uuid*>(arg)); }  },
    {"TextModule" ,     [](void* arg) -> void* { return new TextModule(*static_cast<uuids::uuid*>(arg)); }  },
    {"TransformModule" ,[](void* arg) -> void* { return new TransformModule(*static_cast<uuids::uuid*>(arg)); }  },
    {"TriggerModule" ,  [](void* arg) -> void* { return new TriggerModule(*static_cast<uuids::uuid*>(arg)); }  },
    {"Vector3Module" ,  [](void* arg) -> void* { return new Vector3Module(*static_cast<uuids::uuid*>(arg)); }  },
    {"ImageModule" ,    [](void* arg) -> void* { return new ImageModule(*static_cast<uuids::uuid*>(arg)); }  },
    {"MeshModule" ,     [](void* arg) -> void* { return new MeshModule(*static_cast<uuids::uuid*>(arg)); }  }
};


#endif