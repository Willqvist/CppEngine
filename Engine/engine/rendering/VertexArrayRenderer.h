//
// Created by Gerry on 2020-08-16.
//

#ifndef CPPMC_VERTEXARRAYRENDERER_H
#define CPPMC_VERTEXARRAYRENDERER_H

#include <core/GraphicsLibrary.h>
#include <platform/OpenGL/OpenGLVertexArrayRenderer.h>
#include "VertexArray.h"

namespace VoxEng {
    class VertexArrayRenderer {
    public:
        inline static void draw(Ref <VertexArray> &buffer) {
            switch(GraphicsLibrary::library()) {
                case Library::OPENGL: OpenGLVertexArrayRenderer::draw(buffer);
            }
        }

    protected:
        virtual void drawBuffer(Ref <VertexArray> &buffer) = 0;
    };
}
#endif //CPPMC_VERTEXARRAYRENDERER_H
