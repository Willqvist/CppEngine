//
// Created by Gerry on 2020-08-12.
//
#include "OpenGLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <core/Logger.h>


void VoxEng::OpenGLTexture::bind() {
    bind(0);
}

void VoxEng::OpenGLTexture::bind(int location) {
    glActiveTexture(GL_TEXTURE0 + location);
    glBindTexture(mtextureType, textureId);
}

void VoxEng::OpenGLTexture::unbind() {

}

int VoxEng::OpenGLTexture::width() {
    return 0;
}

int VoxEng::OpenGLTexture::height() {
    return 0;
}

VoxEng::Ref<VoxEng::Texture> VoxEng::OpenGLTexture::subTexture(int x, int y, int width, int height) {
    return CreateRef<OpenGLTexture>(mDetails,textureId,x,y,width,height);
}

VoxEng::OpenGLTexture::~OpenGLTexture() {

}

VoxEng::Ref<VoxEng::OpenGLTexture> VoxEng::OpenGLTexture::create(const char *path, const VoxEng::TextureDetails &details) {
    int imageWidth=0, imageHeight=0, nrChannels;
    unsigned char* data = stbi_load(path, &imageWidth, &imageHeight, &nrChannels, 0);
    unsigned int texture;
    int textureType = convert(details.type);
    int wrap = convert(details.wrapping);
    int min = convert(details.min);
    int max = convert(details.max);
    glGenTextures(1, &texture);
    glBindTexture(textureType, texture);

    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, max);
    if (data) {
        if(nrChannels == 4)
            glTexImage2D(textureType, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        else if(nrChannels == 3)
            glTexImage2D(textureType, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        DEBUG_ERROR("Error loading file: %s - reason: %s\n", path,stbi_failure_reason());
    }
    stbi_image_free(data);

    Ref<OpenGLTexture> tex = CreateRef<OpenGLTexture>(details,texture, 0,0,imageWidth,imageHeight);
    tex->mtextureType = textureType;

    return tex;
}

int VoxEng::OpenGLTexture::convert(VoxEng::TextureWrap wrap) {
    switch(wrap) {
        case TextureWrap::REPEAT: return GL_REPEAT;
        case TextureWrap::MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
        case TextureWrap::CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
        case TextureWrap::CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
    }
    return -1;
}

int VoxEng::OpenGLTexture::convert(VoxEng::TextureFilter filter) {
    switch(filter) {
        case TextureFilter::NEAREST: return GL_NEAREST;
        case TextureFilter::LINEAR: return GL_LINEAR;
    }
    return -1;
}

int VoxEng::OpenGLTexture::convert(VoxEng::TextureType type) {
    switch(type) {
        case TextureType::T_2D: return GL_TEXTURE_2D;
        case TextureType::T_3D: return GL_TEXTURE_3D;
        case TextureType::T_CUBE: return GL_TEXTURE_CUBE_MAP;
    }
    return -1;
}
