//
// Created by Gerry on 2020-08-16.
//

#ifndef CPPMC_VERTEXARRAYRENDERER_H
#define CPPMC_VERTEXARRAYRENDERER_H

#include <glad/glad.h>
#include "core/Core.h"

namespace VoxEng {
    //TODO: change to not use opengl constanrs
    enum RenderMode
    {
        LINES = GL_LINE, POINTS = GL_POINTS, TRIANGLES=GL_TRIANGLES
    };

    class VertexArray;

    class VertexArrayRenderer {
    public:
        static void draw(Ref <VertexArray> &buffer, RenderMode mode);

    protected:
        virtual void drawBuffer(Ref <VertexArray> &buffer) = 0;
    };
}
#endif //CPPMC_VERTEXARRAYRENDERER_H
