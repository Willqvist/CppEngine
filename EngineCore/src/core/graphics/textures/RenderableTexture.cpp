//
// Created by Gerry on 2021-05-12.
//

#include "core/graphics/textures/RenderableTexture.h"

Ziti::RenderableTexture::RenderableTexture(Ziti::FBOBuffers buffers, int width, int height) {
    setDimensions(width,height,0);
    _fbo = FBO::create(width,height,buffers);
}

void Ziti::RenderableTexture::activate() {
    activate(0);
}

void Ziti::RenderableTexture::activate(int location) {
    //printf("activiating texture!!\n");
    //TODO: change this
    if(_fbo->isBuffer(FBOBuffers::COLOR))
        _fbo->getBufferTexture(FBOBuffers::COLOR)->activate(location);
}

void Ziti::RenderableTexture::deactivate() {
    if(_fbo->isBuffer(FBOBuffers::COLOR))
        _fbo->getBufferTexture(FBOBuffers::COLOR)->deactivate();
}

int Ziti::RenderableTexture::width() {
    return viewport().width();
}

int Ziti::RenderableTexture::height() {
    return viewport().height();
}

int Ziti::RenderableTexture::depth() {
    return 0;
}

void Ziti::RenderableTexture::setDimensions(int width, int height, int depth) {
    setViewport(width,height);
}

void Ziti::RenderableTexture::setPixels(unsigned char *data, Ziti::Ownership owns) {

}

void Ziti::RenderableTexture::upload() {

}


//render target!!
void Ziti::RenderableTexture::bind() {
    _fbo->bind();
}

void Ziti::RenderableTexture::unbind() {
    _fbo->unbind();
}

void Ziti::RenderableTexture::clear() {
    bind();
    _fbo->clear();
    unbind();
}

Ziti::Ref<Ziti::Texture> Ziti::RenderableTexture::getBufferTexture(Ziti::FBOBuffers buffers) {
    return _fbo->getBufferTexture(buffers);
}
