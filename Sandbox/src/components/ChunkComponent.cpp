//
// Created by Gerry on 2021-03-16.
//
#include "ChunkComponent.h"
#include "../world/World.h"
#include <tools/Tools.h>
#include <core/ResourceManager.h>
#include "core/Material.h"
#include <rendering/Renderer.h>
#include "rendering/DebugRenderer.h"
#include <rendering/VertexArray.h>
#include "scene/Scene.h"
#include <scene/components/VoxComponent.h>

void ChunkComponent::setChunk(Ref<Chunk> &chunk, int x, int y) {
    this->chunk = chunk;
    setPosition(x,y);
}

void ChunkComponent::setChunkProvider(Ref<World> &world) {
    this->world = world;
}

void ChunkComponent::build() {

}

void ChunkComponent::setView(Ref<VertexArray> &array) {
    this->vertexArray = array;
    visible = true;
}

Ref<Chunk> ChunkComponent::getChunk() {
    return chunk;
}

void ChunkComponent::onCreate() {
    //fprintf(stderr," it took : %d milliseconds\n", (t2-t1));
    Ref<Shader> shader = ResourceManager::loadShader("res/shaders/albedo.glsl");
    material = ResourceManager::createMaterial("AlbedoMaterial",shader);
    material->set("m_Vec2",2.0f);
    material->set("m_Color",glm::vec3(1.0f,1.0f,1.0f));
    material->set("m_albedoTexture",ResourceManager::loadTexture("res/images/texture.png"));
}

Ref<ChunkComponent> ChunkComponent::create(Scene *scene, int x, int z) {
    Entity e = scene->createEntity("chunk");
    Ref<ChunkComponent> c = e.addDynamicComponent<ChunkComponent>();
    c->setPosition(x,z);
    return c;
}

void ChunkComponent::isVisible(bool visible) {
    this->visible = visible;
}

vec2i ChunkComponent::worldPosition() {
    return worldPos;
}

bool ChunkComponent::isDirty() {
    return chunk->isDirty();
}

void ChunkComponent::setPosition(int x, int z){
    component<Transform>().setPosition(x*CHUNK_WIDTH,0,z*CHUNK_DEPTH);
    worldPos.x = x*CHUNK_WIDTH;
    worldPos.y = z*CHUNK_DEPTH;
}

void ChunkComponent::render() {
    if(visible) {
        component<Transform>().setScale({ 1,1,1});
        Renderer::render(vertexArray, material, component<Transform>());
    }
    DebugRenderer::drawCube({ 0,0,0 }, { 255,120,255 },0xFFF);
}

Block ChunkComponent::getBlock(int x, int y, int z)
{
    return chunk->getBlock(x, y, z);
}

void ChunkComponent::setBlock(int x, int y, int z, Block &block)
{
    chunk->setBlock(x, y, z, block);
}

Block *ChunkComponent::getBlocks()
{
    return chunk->getBlocks();
}

void ChunkComponent::setNeighbor(VoxEng::Ref<IChunk> chunk, int neigh)
{
    this->chunk->setNeighbor(chunk, neigh);
}

bool ChunkComponent::hasNeighbor(int neigh)
{
    return chunk->hasNeighbor(neigh);
}

ChunkComponent::~ChunkComponent() {

}
