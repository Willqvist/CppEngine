//
// Created by Gerry on 2021-03-16.
//
#include "DebugRenderer.h"
#include <core/Material.h>
#include <rendering/Renderer.h>
#include "core/ResourceManager.h"
#include <rendering/VertexArray.h>
#include <rendering/Buffer.h>
#include "VertexArrayRenderer.h"

void VoxEng::DebugRenderer::init()
{
    vao = VertexArray::create();
    dataBuffer = ArrayBuffer::create(DEBUG_SIZE);
    indexBuffer = IndexBuffer::create(DEBUG_SIZE);

    dataBuffer->setLayout({
                                  BufferElement(ElementType::float3),
                                  BufferElement(ElementType::float3)
                          });

    vao->addBuffer(dataBuffer);
    transform.setPosition(0, 0, 0);


    material = Material::create(ResourceManager::loadShader("res/shaders/albedo.glsl"));
}

void VoxEng::DebugRenderer::drawCube(glm::vec3 p1, glm::vec3 p7, int color)
{
    glm::vec3 p2 = { p7.x,p1.y,p1.z };
    glm::vec3 p3 = { p7.x,p1.y,p7.z };
    glm::vec3 p4 = { p1.x,p1.y,p7.z };

    glm::vec3 p5 = { p1.x,p7.y,p1.z };
    glm::vec3 p6 = { p7.x,p7.y,p1.z };
    glm::vec3 p8 = { p1.x,p7.y,p7.z };
    drawLines({ p1,p2,p3,p4,p5,p6,p7,p8,p1 }, color);
}

void VoxEng::DebugRenderer::drawLines(const std::initializer_list<glm::vec3> &points, int color)
{
    int startIdx = index / 4;
    for (auto start = points.begin(), end = points.end(); start != end; start ++)
    {
        appendPoint(*start, color);
        indicies[cIdx++] = startIdx++;
    }

}

void VoxEng::DebugRenderer::drawLine(glm::vec3 c1, glm::vec3 c2, glm::vec3 color)
{
    data[index] = c1.x;
    data[index+1] = c1.y;
    data[index+2] = c1.z;
    data[index+3] = color.x;
    data[index + 4] = color.y;
    data[index + 5] = color.z;

    data[index+6] = c2.x;
    data[index+7] = c2.y;
    data[index+8] = c2.z;
    data[index+9] = color.x;
    data[index + 10] = color.y;
    data[index + 11] = color.z;

    index += 12;
}

void VoxEng::DebugRenderer::drawFace(glm::vec3 c1, glm::vec3 c2, glm::vec3 normal, int color) {

}

void VoxEng::DebugRenderer::flush(){
    dataBuffer->data(data, index);
    indexBuffer->data(indicies, cIdx);
    index = 0;
    cIdx = 0;
    printf("RENDERTING DEBUG \n");
    Renderer::pushMode(RenderMode::LINES);
    Renderer::render(vao, material, transform);
    Renderer::popMode();
}

void VoxEng::DebugRenderer::appendPoint(const glm::vec3 &p, int color) {
    if(index + 4 >= DEBUG_SIZE)
    {
        flush();
    }

    data[index] = p.x;
    data[index + 1] = p.y;
    data[index + 2] = p.z;
    data[index + 3] = color;
    index += 4;
}

VoxEng::Ref<VoxEng::VertexArray> VoxEng::DebugRenderer::vao = nullptr;
VoxEng::Ref<VoxEng::ArrayBuffer> VoxEng::DebugRenderer::dataBuffer = nullptr;
VoxEng::Ref<VoxEng::IndexBuffer> VoxEng::DebugRenderer::indexBuffer = nullptr;
VoxEng::Ref<VoxEng::Material> VoxEng::DebugRenderer::material = nullptr;
VoxEng::Transform VoxEng::DebugRenderer::transform;
float VoxEng::DebugRenderer::data[DEBUG_SIZE];
unsigned int VoxEng::DebugRenderer::indicies[DEBUG_SIZE];
int VoxEng::DebugRenderer::cIdx = 0;
int VoxEng::DebugRenderer::index = 0;