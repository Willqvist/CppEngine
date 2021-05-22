//
// Created by Gerry on 2021-05-12.
//

#include <glad/glad.h>
#include <core/graphics/textures/BufferTexture.h>
#include <core/graphics/GraphicsCommand.h>
#include <core/rendering/FramebufferStack.h>
#include "OpenGLFBO.h"
#include "OpenGLTexture.h"

Ziti::OpenGLFBO::OpenGLFBO(int width, int height, Ziti::FBOBuffers buffers) : FBO(width,height,buffers) {
    glGenFramebuffers(1,&_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER,_fbo);
    TextureDetails details;
    if(isBuffer(FBOBuffers::COLOR)) {
        details.internalFormat = TextureFormat::RGBA;
        details.format = TextureFormat::RGBA;
        details.datatype = TextureDataType::UBYTE;
        genTexture(FBOBuffers::COLOR, GL_COLOR_ATTACHMENT0,details);
    }
    if(isBuffer(FBOBuffers::DEPTH_STENCIL)) {
        details.internalFormat = TextureFormat::DEPTH24_STENCIL8;
        details.format = TextureFormat::DEPTH_STENCIL;
        details.datatype = TextureDataType::UINT24_8;
        genTexture(FBOBuffers::DEPTH_STENCIL, GL_DEPTH_STENCIL_ATTACHMENT, details);
    } else {
        //TODO: change details
        if (isBuffer(FBOBuffers::DEPTH)) {
            details.internalFormat = TextureFormat::DEPTH_COMPONENT;
            details.format = TextureFormat::DEPTH_COMPONENT;
            details.datatype = TextureDataType::UINT;
            genTexture(FBOBuffers::DEPTH, GL_DEPTH_ATTACHMENT, details);
        }
        if (isBuffer(FBOBuffers::STENCIL)) {
            genTexture(FBOBuffers::STENCIL, GL_STENCIL_ATTACHMENT, details);
        }
    }

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

    glBindFramebuffer(GL_FRAMEBUFFER,0);

}

void Ziti::OpenGLFBO::bind() {
    FramebufferStack::push(_fbo);
    glViewport(0,0,_width,_height);
    glEnable(GL_DEPTH_TEST);
}

void Ziti::OpenGLFBO::unbind() {
    FramebufferStack::pop();
}

Ziti::Ref<Ziti::Texture> Ziti::OpenGLFBO::getBufferTexture(Ziti::FBOBuffers buffer) {
    return _textures[buffer];
}

void Ziti::OpenGLFBO::genTexture(Ziti::FBOBuffers buffer, unsigned int type, Ziti::TextureDetails& details) {
    Ref<OpenGLTexture> texture = OpenGLTexture::create(details);
    texture->setDimensions(_width,_height,0);
    texture->upload();
    glFramebufferTexture2D(GL_FRAMEBUFFER, type, GL_TEXTURE_2D, texture->textureId(), 0);
    _textures[buffer] = texture;
}


Ziti::OpenGLFBO::~OpenGLFBO() {
    glDeleteFramebuffers(1, &_fbo);
}

void Ziti::OpenGLFBO::clear() {
    //GraphicsCommand::clearScreenColor(0.8f, 0.8f, 1.0f, 1.0f);
    //GraphicsCommand::clear(BUFFER_BIT::COLOR | BUFFER_BIT::DEPTH);
}

