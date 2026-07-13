cmake_minimum_required(VERSION 3.15)
project(WebsocketApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find dependencies that are still external (like Boost and system Threads)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS json) 

# 2. Add ixwebsocket directly from your thirdparty directory
# (Make sure you cloned it into this exact path relative to this CMakeLists file)
add_subdirectory(thirdparty/ixwebsoc)

# 3. Define the executable and its source files
add_executable(client 
    client.cpp 
    
    # Files inside Core/ folder
    ../src/Core/ModuleCore.cpp
    ../src/Core/ModuleRegistry.cpp

    # Files inside src/ folder 
    ../src/LineModule.cpp
    ../src/CameraModule.cpp
    ../src/FileModule.cpp
    ../src/GLTFModule.cpp
    ../src/PointsModule.cpp
    ../src/PrimitiveModule.cpp
    ../src/ScalarModule.cpp
    ../src/TextLogModule.cpp
    ../src/TextModule.cpp
    ../src/TransformModule.cpp
    ../src/TriggerModule.cpp
    ../src/Vector3Module.cpp
    ../src/ImageModule.cpp
    ../src/MeshModule.cpp
    ../src/SceneGraph.cpp
)

# 4. Inclusion des dossiers d'en-tête (Header Include Paths)
target_include_directories(client PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../src         # Lets client.cpp find "../src/Core/ModuleTypes.hpp" cleanly
    ${Boost_INCLUDE_DIRS}
)

# 5. Liens avec les bibliothèques
target_link_libraries(client PRIVATE 
    ixwebsocket                                # Changed from ixwebsocket::ixwebsocket
    Threads::Threads
    Boost::json
)