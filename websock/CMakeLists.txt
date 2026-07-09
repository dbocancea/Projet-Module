cmake_minimum_required(VERSION 3.15)
project(WebsocketApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(ixwebsocket CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS json) 

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

# Inclusion des dossiers d'en-tête (Header Include Paths)
# Permet à CMake de trouver tes fichiers .hpp importés via des chemins relatifs compliqués
target_include_directories(client PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../projetgit/Projet-Module/src/Core
    ${Boost_INCLUDE_DIRS}
)

# Liens avec les bibliothèques
target_link_libraries(client PRIVATE 
    ixwebsocket::ixwebsocket 
    Threads::Threads
    Boost::json
)