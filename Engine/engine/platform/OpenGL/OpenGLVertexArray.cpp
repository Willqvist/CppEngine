//
// Created by Gerry on 2020-08-13.
//

#include <glad/glad.h>
#include <core/Logger.h>
#include "OpenGLVertexArray.h"
#include "OpenGLArrayBuffer.h"

VoxEng::OpenGLVertexArray::OpenGLVertexArray() {
    glGenVertexArrays(1,&vaoId);
}

void VoxEng::OpenGLVertexArray::bind() {
    glBindVertexArray(vaoId);
}

void VoxEng::OpenGLVertexArray::unbind() {
    glBindVertexArray(0);
}

void VoxEng::OpenGLVertexArray::addBuffer(const VoxEng::Ref<VoxEng::ArrayBuffer> &buffer) {

    bind();
    const BufferLayout& layout = buffer->getLayout();
    buffer->bind();
    for(const BufferElement& elem : layout.elements()) {
        switch(elem.type) {
            case ElementType::float1:
            case ElementType::float2:
            case ElementType::float3:
            case ElementType::float4:
            case ElementType::int1:
            case ElementType::int2:
            case ElementType::int3:
            case ElementType::int4:
            case ElementType::boolean:
                glEnableVertexAttribArray(vertexIndex);
                DEBUG_LOG("%d : %d : %#08x : %d : %d",vertexIndex,elem.count(),toOpenGLType(elem.type),layout.stride(),elem.offset);
                glVertexAttribPointer(vertexIndex,elem.count(),toOpenGLType(elem.type),
                        elem.normalized ? GL_TRUE:GL_FALSE,
                        layout.stride(),
                        (const void* )elem.offset);
                vertexIndex ++;
                break;
        }
    }

    mBuffers.push_back(buffer);
}

void VoxEng::OpenGLVertexArray::addIndexBuffer(const VoxEng::Ref<VoxEng::IndexBuffer> &buffer) {
    bind();
    buffer->bind();
    indexBuffer = buffer;
}


VoxEng::OpenGLVertexArray::~OpenGLVertexArray() {
    glDeleteVertexArrays(1,&vaoId);
}

const VoxEng::Ref<VoxEng::IndexBuffer> &VoxEng::OpenGLVertexArray::getIndexBuffer() {
    return indexBuffer;
}

