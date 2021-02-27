//
// Created by Gerry on 2021-02-23.
//

#ifndef CPPMC_WORLDMANAGER_H
#define CPPMC_WORLDMANAGER_H

#include <scene/components/VoxComponent.h>
#include "../world/World.h"
#include "../chunk/Chunk.h"
#include "ChunkComponent.h"
#include "../chunk/ChunkBlockBuilder.h"
#include "../chunk/ChunkModelBuilder.h"

using namespace VoxEng;
class WorldManager: public VoxComponent, public IChunkCreator {
public:
    void onCreate() override {
        VoxComponent::onCreate();
        ChunkModelBuilder::instance()->threads(4);
        ChunkBlockBuilder::instance()->threads(4);

        ChunkBlockBuilder::instance()->finish([this](Ref<ChunkComponent>& c) {
            ChunkModelBuilder::instance()->insert(c);
        });

        ChunkModelBuilder::instance()->finish([this](ChunkModelBuilderData& data) {
            data.chunkComp->setView(data.data);
        });


        world = CreateRef<World>(std::unique_ptr<IChunkCreator>(this));
    }

    Ref<IChunk> createChunk(int x,int y) override {
        Ref<Chunk> chunk = CreateRef<Chunk>();
        Entity e = Scene::active()->createEntity("c");
        Ref<ChunkComponent> comp = e.addDynamicComponent<ChunkComponent>();
        comp->setChunk(chunk,x,y);
        ChunkBlockBuilder::instance()->insert(comp);
        return chunk;
    }

private:
    Ref<World> world;
};


#endif //CPPMC_WORLDMANAGER_H
