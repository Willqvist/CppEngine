//
// Created by Gerry on 2021-03-16.
//
#include "WorldManager.h"
#include "../world/World.h"
#include "../chunk/Chunk.h"
#include "ChunkComponent.h"
#include "../../../build/Sandbox/ChunkTools.h"
#include "../chunk/ChunkBlockBuilder.h"
#include "../chunk/ChunkModelBuilder.h"
#include <scene/Scene.h>
void WorldManager::onCreate() {
    VoxComponent::onCreate();
    ChunkModelBuilder::instance()->threads(4);
    ChunkBlockBuilder::instance()->threads(4);

    ChunkBlockBuilder::instance()->finish([this](Ref<ChunkComponent>& c) {
        //glm::vec3 pos = c->transform().position();
        //int x = pos.x;
        //int z = pos.z;
        /*
        Ref<IChunk> left = world->getChunk(x-1,z);
        Ref<IChunk> right = world->getChunk(x+1,z);
        Ref<IChunk> front = world->getChunk(x,z-1);
        Ref<IChunk> back = world->getChunk(x,z+1);

        if(!left->isDirty() && !right->isDirty() && ! front->isDirty() && !back->isDirty())
         */
        if (hasAllNeighbors(c->getChunk()))
            ChunkModelBuilder::instance()->insert(c);
    });

    ChunkModelBuilder::instance()->finish([this](ChunkModelBuilderData& data) {
        data.chunkComp->setView(data.data);
    });


    world = CreateRef<World>(std::unique_ptr<IChunkCreator>(this));
}

void WorldManager::rebuildChunk(Ref<IChunk> &chunk) {

    {
        Ref<ChunkComponent> c = dynamic_pointer_cast<ChunkComponent>(chunk);

        ChunkModelBuilder::instance()->insert(c);
    }
}

void WorldManager::follow(Entity &follow)
{
    ChunkBlockBuilder::instance()->follow(follow);
    ChunkModelBuilder::instance()->follow(follow);
    world->follow(follow);
}

void WorldManager::update(Timestep ts)
{
    world->update(ts);
}

Ref<IChunk> WorldManager::createChunk(int x, int y) {
    Ref<Chunk> chunk = CreateRef<Chunk>();
    Entity e = Scene::active()->createEntity("c");
    Ref<ChunkComponent> comp = e.addDynamicComponent<ChunkComponent>();
    comp->setChunk(chunk,x,y);
    comp->setChunkProvider(world);
    ChunkBlockBuilder::instance()->insert(comp);
    return comp;
}