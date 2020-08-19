//
// Created by Gerry on 2020-08-13.
//

#include <glad/glad.h>
#include "OpenGLArrayBuffer.h"

VoxEng::OpenGLArrayBuffer::OpenGLArrayBuffer(unsigned int size) {
    glGenBuffers(1,&bufferId);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size,nullptr, GL_DYNAMIC_DRAW);
}

VoxEng::OpenGLArrayBuffer::OpenGLArrayBuffer(float *data, unsigned int size) {
    glGenBuffers(1,&bufferId);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size,data, GL_DYNAMIC_DRAW);
}

void VoxEng::OpenGLArrayBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

void VoxEng::OpenGLArrayBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VoxEng::OpenGLArrayBuffer::data(const void* data, unsigned int size) {
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}


VoxEng::OpenGLArrayBuffer::~OpenGLArrayBuffer() {
    glDeleteBuffers(1, &bufferId);
}