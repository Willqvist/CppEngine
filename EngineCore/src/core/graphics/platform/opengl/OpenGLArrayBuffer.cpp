//
// Created by Gerry on 2020-08-13.
//

#include <glad/glad.h>
#include "OpenGLArrayBuffer.h"

Ziti::OpenGLArrayBuffer::OpenGLArrayBuffer(unsigned int size) {
    _size = size;
    glGenBuffers(1,&_bufferId);
    bind();
    glBufferData(GL_ARRAY_BUFFER, _size*sizeof(float),nullptr, GL_DYNAMIC_DRAW);
}

Ziti::OpenGLArrayBuffer::OpenGLArrayBuffer(float *data, unsigned int size) {
    _size = size;
    glGenBuffers(1,&_bufferId);
    bind();
    glBufferData(GL_ARRAY_BUFFER, _size*sizeof(float),data, GL_STATIC_DRAW);
}

void Ziti::OpenGLArrayBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
}

void Ziti::OpenGLArrayBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Ziti::OpenGLArrayBuffer::data(const void* data, unsigned int size) {
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size*sizeof(float), data);
}


Ziti::OpenGLArrayBuffer::~OpenGLArrayBuffer() {
    glDeleteBuffers(1, &_bufferId);
}