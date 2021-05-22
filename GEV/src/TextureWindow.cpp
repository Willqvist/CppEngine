//
// Created by Gerry on 2021-05-15.
//

#include "TextureWindow.h"

void Ziti::TextureWindow::enableVSync(bool enable) {

}

void Ziti::TextureWindow::update() {

}

void Ziti::TextureWindow::clear() {

}

void Ziti::TextureWindow::swap() {

}

void Ziti::TextureWindow::lockMouse(bool locked) {

}

Ziti::TextureWindow::TextureWindow(Ziti::FBOBuffers buffers, int width,
                                   int height) {
    _texture = CreateRef<RenderableTexture>(buffers,width,height);
    setViewport(width,height);
    //_texture->bind();
}

int Ziti::TextureWindow::width() {
    return viewport().width();
}

int Ziti::TextureWindow::height() {
    return viewport().height();
}

void Ziti::TextureWindow::bind() {
    _texture->bind();
}

void Ziti::TextureWindow::unbind() {
    _texture->unbind();
}

Ziti::Ref<Ziti::RenderableTexture> Ziti::TextureWindow::texture() {
    return _texture;
}
