#ifndef MODULETYPES_HPP
#define MODULETYPES_HPP
#include "ModuleCore.hpp"
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
#include "../ImageModule.hpp"
#include "../MeshModule.hpp"
#include "../SceneGraph.hpp"


using FnModuleTypes = void*(*)(void*);

const map<string ,FnModuleTypes > ModuleTypes = {
    {"ModuleCore" ,     [](void* arg) -> void* { return new ModuleCore(*static_cast<uint128_t*>(arg)); }  },
    {"CameraModule" ,   [](void* arg) -> void* { return new CameraModule(*static_cast<uint128_t*>(arg)); }  },
    {"FileModule" ,     [](void* arg) -> void* { return new FileModule(*static_cast<uint128_t*>(arg)); }  },
  //  {"GLTFModule" ,     [](void* arg) -> void* { return new GLTFModule(*static_cast<uint128_t*>(arg)); }  },
    {"LineModule" ,     [](void* arg) -> void* { return new LineModule(*static_cast<uint128_t*>(arg)); }  },
    {"PointsModule" ,   [](void* arg) -> void* { return new PointsModule(*static_cast<uint128_t*>(arg)); }  },
    {"PrimitiveModule" ,[](void* arg) -> void* { return new PrimitiveModule(*static_cast<uint128_t*>(arg)); }  },
    {"ScalarModule" ,   [](void* arg) -> void* { return new ScalarModule(*static_cast<uint128_t*>(arg)); }  },
    {"TextLogModule" ,  [](void* arg) -> void* { return new TextLogModule(*static_cast<uint128_t*>(arg)); }  },
    {"TextModule" ,     [](void* arg) -> void* { return new TextModule(*static_cast<uint128_t*>(arg)); }  },
    {"TransformModule" ,[](void* arg) -> void* { return new TransformModule(*static_cast<uint128_t*>(arg)); }  },
    {"TriggerModule" ,  [](void* arg) -> void* { return new TriggerModule(*static_cast<uint128_t*>(arg)); }  },
    {"Vector3Module" ,  [](void* arg) -> void* { return new Vector3Module(*static_cast<uint128_t*>(arg)); }  },
 //   {"ImageModule" ,    [](void* arg) -> void* { return new ImageModule(*static_cast<uint128_t*>(arg)); }  },
    {"MeshModule" ,     [](void* arg) -> void* { return new MeshModule(*static_cast<uint128_t*>(arg)); }  },
    {"SceneGraph" ,     [](void* arg) -> void* { (void)arg; return new SceneGraph(); }  }
};


#endif