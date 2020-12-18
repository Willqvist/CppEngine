cmake_minimum_required(VERSION 3.15)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sandbox src/main.cpp src/GameApplication.cpp src/GameApplication.h src/components/CameraMovement.h src/scenes/WorldScene.cpp src/scenes/WorldScene.h src/components/Plane.h src/layers/DebugLayer.cpp src/layers/DebugLayer.h src/components/Rotator.h src/chunk/Chunk.cpp src/chunk/Chunk.h src/chunk/ChunkModelBuilder.cpp src/chunk/ChunkModelBuilder.h src/chunk/ChunkBlockBuilder.cpp src/chunk/ChunkBlockBuilder.h src/tools/EntityCreator.h ../Engine/engine/tools/DataPool.cpp ../Engine/engine/tools/DataPool.h ../Engine/engine/tools/ThreadPool.cpp ../Engine/engine/tools/ThreadPool.h)

target_include_directories(Sandbox PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(Sandbox Engine)