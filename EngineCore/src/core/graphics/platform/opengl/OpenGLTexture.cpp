//
// Created by Gerry on 2020-08-12.
//
#include "OpenGLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glad/glad.h>

Ziti::OpenGLTexture::OpenGLTexture(const Ziti::TextureDetails &details, int textureId, int x, int y, int width,
                                     int height) : Texture(details),_textureId(textureId),_x(x),_y(y),_width(width),_height(height),_textureType(convert(details.type)){}

void Ziti::OpenGLTexture::activate() {
    activate(0);
}

void Ziti::OpenGLTexture::activate(int location) {
    glActiveTexture(GL_TEXTURE0 + location);
    glBindTexture(_textureType, _textureId);
}

void Ziti::OpenGLTexture::deactivate() {

}

int Ziti::OpenGLTexture::width() {
    return _width;
}

int Ziti::OpenGLTexture::height() {
    return _height;
}

int Ziti::OpenGLTexture::depth() {
    return _depth;
}

Ziti::OpenGLTexture::~OpenGLTexture() {
    if(_owns == Ownership::Yes)
        delete[] _data;

}

Ziti::Ref<Ziti::OpenGLTexture> Ziti::OpenGLTexture::create(const char *path, const Ziti::TextureDetails &details) {

    int imageWidth=0, imageHeight=0, nrChannels;
    unsigned char* data = stbi_load(path, &imageWidth, &imageHeight, &nrChannels, 0);
    unsigned int texture;
    glGenTextures(1, &texture);
    Ref<OpenGLTexture> tex = CreateRef<OpenGLTexture>(details,texture, 0,0,imageWidth,imageHeight);
    tex->_details.format = nrChannels == 4 ? TextureFormat::RGBA : TextureFormat::RGB;
    tex->_details.datatype = TextureDataType::UBYTE;
    if (data) {
        tex->setPixels(data,Ownership::No);
        tex->upload();
    }
    else
    {
        printf("Error loading file: %s - reason: %s\n", path,stbi_failure_reason());
    }
    stbi_image_free(data);

    return tex;
}

int Ziti::OpenGLTexture::convert(Ziti::TextureWrap wrap) {
    switch(wrap) {
        case TextureWrap::REPEAT: return GL_REPEAT;
        case TextureWrap::MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
        case TextureWrap::CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
        case TextureWrap::CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
    }
    return -1;
}

int Ziti::OpenGLTexture::convert(Ziti::TextureFilter filter) {
    switch(filter) {
        case TextureFilter::NEAREST: return GL_NEAREST;
        case TextureFilter::LINEAR: return GL_LINEAR;
    }
    return -1;
}

int Ziti::OpenGLTexture::convert(Ziti::TextureType type) {
    switch(type) {
        case TextureType::T_2D: return GL_TEXTURE_2D;
        case TextureType::T_3D: return GL_TEXTURE_3D;
        case TextureType::T_CUBE: return GL_TEXTURE_CUBE_MAP;
    }
    return -1;
}

int Ziti::OpenGLTexture::convert(Ziti::TextureFormat format) {
    switch(format) {
        case TextureFormat::RGBA: return GL_RGBA;
        case TextureFormat::RGB: return GL_RGB;
        case TextureFormat::RED: return GL_RED;
        case TextureFormat::DEPTH_COMPONENT: return GL_DEPTH_COMPONENT;
        case TextureFormat::DEPTH_STENCIL: return GL_DEPTH_STENCIL;
        case TextureFormat::DEPTH24_STENCIL8: return GL_DEPTH24_STENCIL8;
    }
    return -1;
}

int Ziti::OpenGLTexture::convert(Ziti::TextureDataType type) {
    switch(type) {
        case TextureDataType::UBYTE: return GL_UNSIGNED_BYTE;
        case TextureDataType::UINT24_8: return GL_UNSIGNED_INT_24_8;
        case TextureDataType::UINT: return GL_UNSIGNED_INT;
        case TextureDataType::FLOAT: return GL_FLOAT;
    }
    return -1;
}

#define IGTZ(val,n_val) val = n_val < 0 ? val : n_val
void Ziti::OpenGLTexture::setDimensions(int width, int height, int depth) {
    IGTZ(_width,width);
    IGTZ(_depth,depth);
    IGTZ(_height,height);
}

void Ziti::OpenGLTexture::setPixels(unsigned char *data, Ziti::Ownership owns) {
    if(owns == Ownership::Yes) {
        delete[] _data;
    }
    _owns = owns;
    _data = data;
}

void Ziti::OpenGLTexture::upload() {
    int textureFormat = convert(_details.format);
    int intTextureFormat = convert(_details.internalFormat);
    int textureDataType = convert(_details.datatype);

    int wrap = convert(_details.wrapping);
    int min = convert(_details.min);
    int max = convert(_details.max);
    glBindTexture(_textureType, _textureId);
    glTexParameteri(_textureType, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(_textureType, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(_textureType, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(_textureType, GL_TEXTURE_MAG_FILTER, max);
    printf("HERE! %d \n",_details.format);
    switch(_details.type) {
        case TextureType::T_2D:
            glTexImage2D(_textureType, 0, intTextureFormat, _width, _height, 0, textureFormat, textureDataType, _data);
            break;

        case TextureType::T_3D:
            glTexImage3D(_textureType, 0, intTextureFormat, _width, _height, _depth, 0, textureFormat, textureDataType, _data);
            break;
    }
    glBindTexture(_textureType, 0);
}

Ziti::Ref<Ziti::OpenGLTexture> Ziti::OpenGLTexture::create(const Ziti::TextureType &type) {
    TextureDetails details;
    details.type = type;
    return create(details);
}

int Ziti::OpenGLTexture::textureId() {
    return _textureId;
}

Ziti::Ref<Ziti::OpenGLTexture> Ziti::OpenGLTexture::create(const Ziti::TextureDetails &details) {
    unsigned int texture;
    glGenTextures(1, &texture);
    return CreateRef<OpenGLTexture>(details,texture, 0,0,0,0);
}

