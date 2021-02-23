//
// Created by Gerry on 2020-08-16.
//

#ifndef CPPMC_OPENGLVERTEXARRAYRENDERER_H
#define CPPMC_OPENGLVERTEXARRAYRENDERER_H

#include <rendering/VertexArrayRenderer.h>
#include <glad/glad.h>
#include <core/Logger.h>

namespace VoxEng {
    class OpenGLVertexArrayRenderer {
    public:
        inline static void draw(Ref<VertexArray> &buffer) {
            buffer->bind();
            Ref<IndexBuffer> ibo = buffer->getIndexBuffer();
            if(ibo) {
                ibo->bind();
                glDrawElements(GL_TRIANGLES, ibo->getSize(),GL_UNSIGNED_INT,nullptr);
            } else {
                glDrawArrays(GL_TRIANGLES,0,buffer->buffers()[0]->size/3);
            }

        }
    };
}


#endif //CPPMC_OPENGLVERTEXARRAYRENDERER_H
