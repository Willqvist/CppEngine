cmake_minimum_required(VERSION 3.15)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sandbox src/main.cpp src/GameApplication.cpp src/GameApplication.h src/components/CameraMovement.h src/scenes/WorldScene.cpp src/scenes/WorldScene.h src/layers/DebugLayer.cpp src/layers/DebugLayer.h src/chunk/Chunk.cpp src/chunk/Chunk.h src/chunk/ChunkModelBuilder.h src/chunk/ChunkBlockBuilder.h src/tools/EntityCreator.h ../Engine/engine/tools/DataPool.h ../Engine/engine/threading/ThreadPool.cpp ../Engine/engine/threading/ThreadPool.h src/chunk/Block.h src/components/ChunkComponent.h src/chunk/Block.cpp src/chunk/blockdata/BlockVerticies.h src/chunk/blockdata/VoxelBlock.cpp src/chunk/blockdata/VoxelBlock.h src/chunk/blockdata/BlockFaceData.h src/chunk/blockdata/BlockFaceData.cpp src/chunk/blockdata/BlockUvs.h src/chunk/blockdata/BasicUVBlock.cpp src/chunk/blockdata/BasicUVBlock.h src/world/World.cpp src/world/World.h src/world/IChunkCreator.h src/chunk/IChunk.h src/components/WorldManager.h src/chunk/ChunkBlockBuilder.cpp src/chunk/ChunkModelBuilder.cpp src/components/CameraMovement.cpp src/components/ChunkComponent.cpp src/components/WorldManager.cpp)

target_include_directories(Sandbox PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(Sandbox Engine)