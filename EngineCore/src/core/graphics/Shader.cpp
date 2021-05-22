//
// Created by Gerry on 2020-08-17.
//

#include <core/graphics/GraphicsCore.h>
#include "core/graphics/Shader.h"
#include "platform/OpenGL/OpenGLShader.h"

Ziti::Ref <Ziti::Shader> Ziti::Shader::create(const ShaderData& data, ShaderLayout& layout) {
    /*
    switch (GraphicsLibrary::api()) {
        case Library::OPENGL:
                return CreateRef<OpenGLShader>(data, layout);
            break;
    }
     */
    return nullptr;
}

Ziti::Ref<Ziti::Shader> Ziti::Shader::create(const Ziti::ShaderData &data) {
    ShaderLayout layout({{"position",0}});
    switch (GraphicsCore::api()) {
        case GraphicsAPI::OPENGL:
            return CreateRef<OpenGLShader>(data, layout);
            break;
    }
    return nullptr;
}

Ziti::ShaderLayout::ShaderLayout(std::vector<ShaderLayoutLocation> elements) : _elements(elements) {}

Ziti::ShaderLayout::ShaderLayout(const std::initializer_list<ShaderLayoutLocation> elements) : _elements(elements) {}