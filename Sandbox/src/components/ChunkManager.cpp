//
// Created by Gerry on 2021-01-21.
//
#include "ChunkManager.h"
#include "scene/Scene.h"
#include "../chunk/ChunkBlockBuilder.h"

void ChunkManager::onCreate() {

}

void ChunkManager::setScene(Scene *scene) {
    this->scene = scene;
    Ref<Chunk> chunk = CreateRef<Chunk>();
    this->chunk = ChunkModelBuilder::generate(chunk);

    mat = ResourceManager::createMaterial("chunk",ResourceManager::loadShader("res/shaders/albedo.glsl"));
}

void ChunkManager::generate() {
    int halfDist = 12;
    int t = getTime();
    for(int x = -halfDist; x <= halfDist; x++) {
        for(int z = -halfDist; z <= halfDist; z++) {
            Ref<ChunkComponent> chunkComp = ChunkComponent::create(scene,x,z);
        }
    }
    fprintf(stderr," it took: %d ms to generate %d chunks \n",getTime()-t,(halfDist*2+1)*2);
}
