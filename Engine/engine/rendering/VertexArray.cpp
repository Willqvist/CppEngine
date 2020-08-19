//
// Created by Gerry on 2020-08-13.
//

#include <core/GraphicsLibrary.h>
#include <platform/OpenGL/OpenGLVertexArray.h>
#include "VertexArray.h"

VoxEng::Ref<VoxEng::VertexArray> VoxEng::VertexArray::create() {
    switch(GraphicsLibrary::library()) {
        case Library::OPENGL: return CreateRef<OpenGLVertexArray>();
    }
    return nullptr;
}
