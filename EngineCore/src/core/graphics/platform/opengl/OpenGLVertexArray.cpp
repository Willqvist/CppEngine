//
// Created by Gerry on 2020-08-13.
//

#include <glad/glad.h>
#include "OpenGLVertexArray.h"
#include "OpenGLArrayBuffer.h"

Ziti::OpenGLVertexArray::OpenGLVertexArray() {
    glGenVertexArrays(1,&_vaoId);
}

void Ziti::OpenGLVertexArray::bind() {
    glBindVertexArray(_vaoId);
}

void Ziti::OpenGLVertexArray::unbind() {
    glBindVertexArray(0);
}

void Ziti::OpenGLVertexArray::addBuffer(const Ziti::Ref<Ziti::ArrayBuffer> &buffer) {

    bind();
    const BufferLayout& layout = buffer->getLayout();
    buffer->bind();
    for(const BufferElement& elem : layout.elements()) {
        switch(elem._type) {
            case ElementType::float1:
            case ElementType::float2:
            case ElementType::float3:
            case ElementType::float4:
            case ElementType::int1:
            case ElementType::int2:
            case ElementType::int3:
            case ElementType::int4:
            case ElementType::boolean:
                glEnableVertexAttribArray(_vertexIndex);
                fprintf(stderr,"%d : %d : %#08x : %d : %d\n",_vertexIndex,elem.count(),toOpenGLType(elem._type),layout.stride(),elem._offset);
                glVertexAttribPointer(_vertexIndex,elem.count(),toOpenGLType(elem._type),
                        elem._normalized ? GL_TRUE:GL_FALSE,
                        layout.stride(),
                        (const void* )elem._offset);
                _vertexIndex ++;
                break;
        }
    }

    _buffers.push_back(buffer);
}

void Ziti::OpenGLVertexArray::addIndexBuffer(const Ziti::Ref<Ziti::IndexBuffer> &buffer) {
    bind();
    buffer->bind();
    _indexBuffer = buffer;
}


Ziti::OpenGLVertexArray::~OpenGLVertexArray() {
    
    glDeleteVertexArrays(1,&_vaoId);
}

const Ziti::Ref<Ziti::IndexBuffer> &Ziti::OpenGLVertexArray::getIndexBuffer() {
    return _indexBuffer;
}

