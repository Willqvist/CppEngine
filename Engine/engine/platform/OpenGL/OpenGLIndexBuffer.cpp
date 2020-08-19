//
// Created by Gerry on 2020-08-16.
//
#include <glad/glad.h>
#include "OpenGLIndexBuffer.h"

VoxEng::OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int *data, unsigned int size) {
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size,data, GL_STATIC_DRAW);
    this->size = size/ sizeof(int);
}

VoxEng::OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int size) {
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size,nullptr, GL_DYNAMIC_DRAW);
    this->size = size/ sizeof(int);
}

void VoxEng::OpenGLIndexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}

void VoxEng::OpenGLIndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VoxEng::OpenGLIndexBuffer::data(const unsigned int *data, unsigned int size) {
    bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,size,data);
}

VoxEng::OpenGLIndexBuffer::~OpenGLIndexBuffer() {
    glDeleteBuffers(1,&bufferId);
}

unsigned int VoxEng::OpenGLIndexBuffer::getSize() {
    return size;
}

