//
// Created by Gerry on 2020-08-16.
//
#include <glad/glad.h>
#include "OpenGLIndexBuffer.h"

Ziti::OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int *data, unsigned int size) {
    glGenBuffers(1, &_bufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(int),data, GL_STATIC_DRAW);
    _size = size;
}

Ziti::OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int size) {
    glGenBuffers(1, &_bufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(int),nullptr, GL_DYNAMIC_DRAW);
    _size = size;
}

void Ziti::OpenGLIndexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
}

void Ziti::OpenGLIndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Ziti::OpenGLIndexBuffer::data(const unsigned int *data, unsigned int size) {
    bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,size*sizeof(unsigned int),data);
}

Ziti::OpenGLIndexBuffer::~OpenGLIndexBuffer() {
    glDeleteBuffers(1,&_bufferId);
}

unsigned int Ziti::OpenGLIndexBuffer::getSize() {
    return _size;
}

