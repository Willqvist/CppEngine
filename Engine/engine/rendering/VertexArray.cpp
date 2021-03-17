//
// Created by Gerry on 2020-08-13.
//

#include <core/GraphicsLibrary.h>
#include <platform/OpenGL/OpenGLVertexArray.h>
#include "VertexArray.h"
#include "Buffer.h"

VoxEng::Ref<VoxEng::VertexArray> VoxEng::VertexArray::create() {
    switch(GraphicsLibrary::library()) {
        case Library::OPENGL: return CreateRef<OpenGLVertexArray>();
    }
    return nullptr;
}

const std::vector<VoxEng::Ref<VoxEng::ArrayBuffer>>& VoxEng::VertexArray::buffers() {return mBuffers; }