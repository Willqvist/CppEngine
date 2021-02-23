//
// Created by Gerry on 2021-02-23.
//

#ifndef CPPMC_WORLDMANAGER_H
#define CPPMC_WORLDMANAGER_H

#include <scene/components/VoxComponent.h>
#include "../world/World.h"
#include "../chunk/Chunk.h"
#include "ChunkComponent.h"

using namespace VoxEng;
class WorldManager: public VoxComponent, public IChunkCreator {
public:
    void onCreate() override {
        VoxComponent::onCreate();
        ChunkModelBuilder::threads(2);
        world = CreateRef<World>(std::unique_ptr<IChunkCreator>(this));
    }

    Ref<IChunk> createChunk() override {
        Ref<Chunk> chunk = CreateRef<Chunk>();
        Entity e = Scene::active()->createEntity("c");
        Ref<ChunkComponent> comp = e.addDynamicComponent<ChunkComponent>();
        comp->setChunk(chunk,0,0);
        return chunk;
    }

private:
    Ref<World> world;
};


#endif //CPPMC_WORLDMANAGER_H
