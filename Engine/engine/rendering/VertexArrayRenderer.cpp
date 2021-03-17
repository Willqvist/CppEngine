//
// Created by Gerry on 2021-03-16.
//
#include "VertexArrayRenderer.h"
#include <platform/OpenGL/OpenGLVertexArrayRenderer.h>
#include <core/GraphicsLibrary.h>

void VoxEng::VertexArrayRenderer::draw(VoxEng::Ref<VoxEng::VertexArray> &buffer, VoxEng::RenderMode mode) {
    switch(GraphicsLibrary::library()) {
        case Library::OPENGL: OpenGLVertexArrayRenderer::draw(buffer, mode);
    }
}