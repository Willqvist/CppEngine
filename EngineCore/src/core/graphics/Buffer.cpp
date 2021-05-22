//
// Created by Gerry on 2020-08-13.
//
#include <core/Memory.h>
#include <core/graphics/GraphicsCore.h>
#include "core/graphics/Buffer.h"
#include "platform/OpenGL/OpenGLArrayBuffer.h"
#include "platform/OpenGL/OpenGLIndexBuffer.h"

static unsigned int primativeSize(Ziti::ElementType type) {
    switch(type) {
        case Ziti::ElementType::float1: return 4;
        case Ziti::ElementType::float2: return 4*2;
        case Ziti::ElementType::float3: return 4*3;
        case Ziti::ElementType::float4: return 4*4;
        case Ziti::ElementType::mat3: return 4*3*3;
        case Ziti::ElementType::mat4: return 4*4*4;
        case Ziti::ElementType::int1: return 4;
        case Ziti::ElementType::int2: return 4*2;
        case Ziti::ElementType::int3: return 4*3;
        case Ziti::ElementType::int4: return 4*4;
        case Ziti::ElementType::boolean: return 1;
    }
    return -1;
}

Ziti::BufferLayout::BufferLayout(const std::initializer_list<BufferElement> elements): _elements(elements) {
    calculateElements();
}

Ziti::BufferLayout::BufferLayout(const std::initializer_list<ElementType> elements) {
    for(const ElementType& type : elements) {
        _elements.push_back(BufferElement(type,false));
    }
    calculateElements();
}

Ziti::BufferElement::BufferElement(Ziti::ElementType type, bool normalized): _type(type), _size(primativeSize(type)), _offset(0), _normalized(normalized) {}

Ziti::Ref<Ziti::ArrayBuffer> Ziti::ArrayBuffer::create(unsigned int size) {
    switch(GraphicsCore::api()) {
        case GraphicsAPI::OPENGL: return CreateRef<OpenGLArrayBuffer>(size);
    }
    return nullptr;
}

Ziti::Ref<Ziti::ArrayBuffer> Ziti::ArrayBuffer::create(float *vertices, unsigned int size) {
    switch(GraphicsCore::api()) {
        case GraphicsAPI::OPENGL: return CreateRef<OpenGLArrayBuffer>(vertices, size);
    }
    return nullptr;
}

Ziti::Ref<Ziti::IndexBuffer> Ziti::IndexBuffer::create(unsigned int size) {
    switch(GraphicsCore::api()) {
        case GraphicsAPI::OPENGL: return CreateRef<OpenGLIndexBuffer>(size);
    }
    return nullptr;
}

Ziti::Ref<Ziti::IndexBuffer> Ziti::IndexBuffer::create(unsigned int *vertices, unsigned int size) {
    switch(GraphicsCore::api()) {
        case GraphicsAPI::OPENGL: return CreateRef<OpenGLIndexBuffer>(vertices, size);
    }
    return nullptr;
}

const std::vector<Ziti::BufferElement> &Ziti::BufferLayout::elements() const  { return _elements; }

unsigned int Ziti::BufferLayout::stride() const  {return _stride;}

void Ziti::BufferLayout::calculateElements() {
    int offset = 0;
    _stride = 0;
    for(BufferElement& e : _elements) {
        e._offset = offset;
        offset += e._size;
        _stride += e._size;
    }
}


unsigned int Ziti::BufferElement::count() const {
    switch(_type) {
        case ElementType::float1: return 1;
        case ElementType::float2: return 2;
        case ElementType::float3: return 3;
        case ElementType::float4: return 4;
        case ElementType::mat3: return 3;
        case ElementType::mat4: return 4;
        case ElementType::int1: return 1;
        case ElementType::int2: return 2;
        case ElementType::int3: return 3;
        case ElementType::int4: return 4;
        case ElementType::boolean: return 1;
    }
    return -1;
}
