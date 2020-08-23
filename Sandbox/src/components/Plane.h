//
// Created by Gerry on 2020-08-23.
//

#ifndef CPPMC_PLANE_H
#define CPPMC_PLANE_H

#include <scene/components/VoxComponent.h>
#include <rendering/VertexArray.h>
#include <core/Material.h>
#include <core/ResourceManager.h>
#include <rendering/Renderer.h>

using namespace VoxEng;
class Plane: public VoxComponent {
public:
    void onCreate() override {
        this->transform = &component<Transform>();
        vertexArray = VertexArray::create();

        float arr[8] = {
                -1.5f, -1.5f,
                1.5f, -1.5f,
                1.5f, 1.5f,
                -1.5f, 1.5f
        };

        unsigned int indexArray[6] = {
                0,1,2,
                2,3,0
        };

        Ref<ArrayBuffer> buffer = ArrayBuffer::create(arr, 8*sizeof(float));
        Ref<IndexBuffer> ibo = IndexBuffer::create(indexArray, 6*sizeof(unsigned int));
        BufferLayout layout({
                                    BufferElement(ElementType::float2)
                            });
        buffer->setLayout(layout);

        vertexArray->addBuffer(buffer);
        vertexArray->addIndexBuffer(ibo);
        Ref<Shader> shader = ResourceManager::loadShader("res/shaders/albedo.glsl");
        material = ResourceManager::createMaterial("AlbedoMaterial",shader);
        material->set("m_Vec2",2.0f);
        material->set("m_albedoTexture",ResourceManager::loadTexture("res/images/img.png"));
        material->set("m_Color",glm::vec3(1.0f,1.0f,0.0f));
    }

    void render() override {
        //VoxComponent::render();
        Renderer::render(vertexArray, material,*transform);
    }
    Ref<Material> material;
private:
    Transform* transform;
    Ref<VertexArray> vertexArray;
};
#endif //CPPMC_PLANE_H