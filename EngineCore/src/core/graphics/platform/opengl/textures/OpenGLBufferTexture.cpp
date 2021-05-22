//
// Created by Gerry on 2021-05-12.
//

#include <glad/glad.h>
#include "OpenGLBufferTexture.h"

Ziti::OpenGLBufferTexture::OpenGLBufferTexture(Ziti::BufferTextureType type, int width, int height) : BufferTexture(
        type, width, height) {
    glGenRenderbuffers(1, &_rbo);
    activate();
    //TODO: change to convert(type) instead of GL_DEPTH24_STENCIL8.
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
    deactivate();
}

void Ziti::OpenGLBufferTexture::activate() {
    activate(0);
}

void Ziti::OpenGLBufferTexture::activate(int location) {
    glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
}

void Ziti::OpenGLBufferTexture::deactivate() {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

int Ziti::OpenGLBufferTexture::width() {
    return _width;
}

int Ziti::OpenGLBufferTexture::height() {
    return _height;
}

int Ziti::OpenGLBufferTexture::depth() {
    return 0;
}

void Ziti::OpenGLBufferTexture::setDimensions(int width, int height, int depth) {
    _width = width;
    _height = height;
}

void Ziti::OpenGLBufferTexture::setPixels(unsigned char *data, Ziti::Ownership owns) {

}

void Ziti::OpenGLBufferTexture::upload() {
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);
}
