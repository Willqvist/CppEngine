//
// Created by Gerry on 2021-02-23.
//

#include "World.h"
#include "core/Timestep.h"
#include "../chunk/IChunk.h"
#include "../../../build/Sandbox/ChunkTools.h"
#include "scene/components/Transform.h"
#include "IChunkCreator.h"

World::World(Scope<IChunkCreator> &chunkCreator) : chunkCreator(std::move(chunkCreator)) {

}

void World::follow(Entity &follow)
{
    following = follow;
}

void World::viewDistance(float dist)
{
    viewDist = dist / 2.0f;
}

void World::update(Timestep step) {
    if (following.valid()) {
        Transform& trans = following.getComponent<Transform>();
        float x = trans.position().x/ CHUNK_WIDTH;
        float z = trans.position().z / CHUNK_DEPTH;
        for (int i = x - viewDist; i < x + viewDist; i++) {
            for (int j = z - viewDist; j < z + viewDist; j++) {
                vec2i pos = { i,j };
                if (getChunk(i,j) != nullptr)
                {
                    //chunk already exists.
                    continue;
                }
                Ref<IChunk> c = this->chunkCreator->createChunk(i, j);
                fillNeighbors(pos, c);
                chunkMap[pos] = c;
            }
        }
    }
}

Ref<IChunk> World::getChunk(int x, int z) {
    vec2i key = {x,z};
    if(chunkMap.find(key) == chunkMap.end())
        return nullptr;
    return chunkMap[key];
}

bool World::chunkExists(vec2i pos) {
    return this->chunkMap.find(pos) != chunkMap.end();
}

void World::fillNeighbors(vec2i pos, Ref<IChunk> &chunk) {
    vec2i key;
    if (chunkExists(key = { pos.x - 1,pos.y })) {
        Ref<IChunk> n = chunkMap[key];
        n->setNeighbor(chunk, CRIGHT);
        chunk->setNeighbor(n, CLEFT);
        if(hasAllNeighbors(n))
            chunkCreator->rebuildChunk(n);

    }
    if (chunkExists(key = { pos.x + 1,pos.y })) {
        Ref<IChunk> n = chunkMap[key];
        n->setNeighbor(chunk, CLEFT);
        chunk->setNeighbor(n, CRIGHT);
        if (hasAllNeighbors(n))
            chunkCreator->rebuildChunk(n);
    }
    if (chunkExists(key = { pos.x,pos.y + 1 })) {
        Ref<IChunk> n = chunkMap[key];
        n->setNeighbor(chunk, CBACK);
        chunk->setNeighbor(n, CFRONT);
        if (hasAllNeighbors(n))
            chunkCreator->rebuildChunk(n);
    }
    if (chunkExists(key = { pos.x,pos.y - 1 })) {
        Ref<IChunk> n = chunkMap[key];
        n->setNeighbor(chunk, CFRONT);
        chunk->setNeighbor(n, CBACK);
        if (hasAllNeighbors(n))
            chunkCreator->rebuildChunk(n);
    }

    if (hasAllNeighbors(chunk)) {
        chunkCreator->rebuildChunk(chunk);
    }
}