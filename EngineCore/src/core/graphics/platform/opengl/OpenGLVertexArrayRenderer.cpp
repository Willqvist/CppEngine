//
// Created by Gerry on 2021-03-16.
//
#include <core/graphics/Buffer.h>
#include <glad/glad.h>
#include "OpenGLVertexArrayRenderer.h"
#include <core/graphics/VertexArray.h>
namespace Ziti {
    void OpenGLVertexArrayRenderer::draw(Ref<VertexArray> &buffer, int mode) {
        buffer->bind();
        Ref<IndexBuffer> ibo = buffer->getIndexBuffer();
        if (ibo) {
            ibo->bind();
            glDrawElements(mode, ibo->getSize(), GL_UNSIGNED_INT, nullptr);
        } else {
            glDrawArrays(mode, 0, buffer->buffers()[0]->_size / 3);
        }
    }
}