//
// Created by Gerry on 2020-08-13.
//
#include <core/GraphicsLibrary.h>
#include <platform/OpenGL/OpenGLArrayBuffer.h>
#include <platform/OpenGL/OpenGLIndexBuffer.h>
#include "Buffer.h"

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
