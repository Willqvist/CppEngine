//
// Created by Gerry on 2021-01-14.
//

#ifndef CPPMC_CHUNKCOMPONENT_H
#define CPPMC_CHUNKCOMPONENT_H

#include <scene/components/VoxComponent.h>
#include "../chunk/Chunk.h"
#include "../chunk/ChunkModelBuilder.h"
#include <tools/Tools.h>
#include <core/ResourceManager.h>
#include <rendering/Renderer.h>

using namespace VoxEng;
class ChunkComponent: public VoxComponent {
public:

    void setChunk(Ref<Chunk>& chunk,int x,int y) {
        this->chunk = chunk;
        vertexArray = ChunkModelBuilder::generate(chunk);
        ChunkModelBuilder::build(*chunk);
        visible = true;
        this->setPosition(x,y);
    }

    void onCreate() override {
        VoxComponent::onCreate();
        //fprintf(stderr," it took : %d milliseconds\n", (t2-t1));
        Ref<Shader> shader = ResourceManager::loadShader("res/shaders/albedo.glsl");
        material = ResourceManager::createMaterial("AlbedoMaterial",shader);
        material->set("m_Vec2",2.0f);
        material->set("m_Color",glm::vec3(1.0f,1.0f,1.0f));
        material->set("m_albedoTexture",ResourceManager::loadTexture("res/images/texture.png"));
    }

    static Ref<ChunkComponent> create(Scene* scene, int x,int z) {
        Entity e = scene->createEntity("chunk");
        Ref<ChunkComponent> c = e.addDynamicComponent<ChunkComponent>();
        c->setPosition(x,z);
        return c;
    }

    void isVisible(bool visible) {
        this->visible = visible;
    }

    void setPosition(int x,int z) {
        component<Transform>().setPosition(x*CHUNK_WIDTH,0,z*CHUNK_DEPTH);
    }

    void render() override {
        if(visible)
            Renderer::render(vertexArray,material, component<Transform>());
    }

    ~ChunkComponent() override {
    }
private:
    Ref<Chunk> chunk;
    Ref<VertexArray> vertexArray;
    Ref<Material> material;
    bool visible = false;
};
#endif //CPPMC_CHUNKCOMPONENT_H
