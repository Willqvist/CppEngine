//
// Created by Gerry on 2021-03-16.
//
#include <core/graphics/GraphicsCore.h>
#include "core/graphics/VertexArrayRenderer.h"
#include "platform/OpenGL/OpenGLVertexArrayRenderer.h"

void Ziti::VertexArrayRenderer::draw(Ziti::Ref<Ziti::VertexArray> &buffer, Ziti::RenderMode mode) {
    switch(GraphicsCore::api()) {
        case GraphicsAPI::OPENGL: OpenGLVertexArrayRenderer::draw(buffer, mode);
    }
}