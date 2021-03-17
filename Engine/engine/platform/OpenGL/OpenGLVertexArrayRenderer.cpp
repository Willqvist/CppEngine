//
// Created by Gerry on 2021-03-16.
//
#include "OpenGLVertexArrayRenderer.h"
#include <rendering/VertexArrayRenderer.h>
#include <rendering/Buffer.h>
#include <rendering/VertexArray.h>
void VoxEng::OpenGLVertexArrayRenderer::draw(VoxEng::Ref<VoxEng::VertexArray> &buffer, int mode) {
    buffer->bind();
    Ref<IndexBuffer> ibo = buffer->getIndexBuffer();
    if(ibo) {
        ibo->bind();
        glDrawElements(mode, ibo->getSize(),GL_UNSIGNED_INT,nullptr);
    } else {
        glDrawArrays(mode,0,buffer->buffers()[0]->size/3);
    }
}