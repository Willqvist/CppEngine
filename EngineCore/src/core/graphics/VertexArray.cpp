//
// Created by Gerry on 2020-08-13.
//

#include <core/graphics/GraphicsCore.h>
#include "core/graphics/VertexArray.h"
#include "core/graphics/Buffer.h"
#include "platform/OpenGL/OpenGLVertexArray.h"

Ziti::Ref<Ziti::VertexArray> Ziti::VertexArray::create() {
    switch(GraphicsCore::api()) {
        case GraphicsAPI::OPENGL: return CreateRef<OpenGLVertexArray>();
    }
    return nullptr;
}

const std::vector<Ziti::Ref<Ziti::ArrayBuffer>>& Ziti::VertexArray::buffers() {return _buffers; }