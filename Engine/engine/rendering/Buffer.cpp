//
// Created by Gerry on 2020-08-13.
//
#include <core/GraphicsLibrary.h>
#include <platform/OpenGL/OpenGLArrayBuffer.h>
#include <platform/OpenGL/OpenGLIndexBuffer.h>
#include "Buffer.h"

static unsigned int elementPrimativeSize(VoxEng::ElementType type) {
    switch(type) {
        case VoxEng::ElementType::float1: return 4;
        case VoxEng::ElementType::float2: return 4*2;
        case VoxEng::ElementType::float3: return 4*3;
        case VoxEng::ElementType::float4: return 4*4;
        case VoxEng::ElementType::mat3: return 4*3*3;
        case VoxEng::ElementType::mat4: return 4*4*4;
        case VoxEng::ElementType::int1: return 4;
        case VoxEng::ElementType::int2: return 4*2;
        case VoxEng::ElementType::int3: return 4*3;
        case VoxEng::ElementType::int4: return 4*4;
        case VoxEng::ElementType::boolean: return 1;
    }
    return -1;
}

VoxEng::BufferLayout::BufferLayout(const std::initializer_list<BufferElement> elements): mElements(elements) {
    calculateElements();
}

VoxEng::BufferElement::BufferElement(VoxEng::ElementType type, bool normalized): type(type), size(elementPrimativeSize(type)), offset(0), normalized(normalized){}

VoxEng::Ref<VoxEng::ArrayBuffer> VoxEng::ArrayBuffer::create(unsigned int size) {
    switch(GraphicsLibrary::library()) {
        case Library::OPENGL: return CreateRef<OpenGLArrayBuffer>(size);
    }
    return nullptr;
}

VoxEng::Ref<VoxEng::ArrayBuffer> VoxEng::ArrayBuffer::create(float *vertices, unsigned int size) {
    switch(GraphicsLibrary::library()) {
        case Library::OPENGL: return CreateRef<OpenGLArrayBuffer>(vertices, size);
    }
    return nullptr;
}

VoxEng::Ref<VoxEng::IndexBuffer> VoxEng::IndexBuffer::create(unsigned int size) {
    switch(GraphicsLibrary::library()) {
        case Library::OPENGL: return CreateRef<OpenGLIndexBuffer>(size);
    }
    return nullptr;
}

VoxEng::Ref<VoxEng::IndexBuffer> VoxEng::IndexBuffer::create(unsigned int *vertices, unsigned int size) {
    switch(GraphicsLibrary::library()) {
        case Library::OPENGL: return CreateRef<OpenGLIndexBuffer>(vertices,size);
    }
    return nullptr;
}

const std::vector<VoxEng::BufferElement> &VoxEng::BufferLayout::elements() const  { return mElements; }

unsigned int VoxEng::BufferLayout::stride() const  {return mStride;}

void VoxEng::BufferLayout::calculateElements() {
    int offset = 0;
    mStride = 0;
    for(BufferElement& e : mElements) {
        e.offset = offset;
        offset += e.size;
        mStride += e.size;
    }
}

unsigned int VoxEng::BufferElement::count() const {
    switch(type) {
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
