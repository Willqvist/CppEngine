//
// Created by Gerry on 2020-08-17.
//

#include <core/GraphicsLibrary.h>
#include <platform/OpenGL/OpenGLShader.h>
#include "Shader.h"

VoxEng::Ref <VoxEng::Shader> VoxEng::Shader::create(const std::string& vertex, const std::string& fragment, ShaderLayout& layout) {
    switch (GraphicsLibrary::library()) {
        case Library::OPENGL:
                return CreateRef<OpenGLShader>(vertex, fragment,layout);
            break;
    }
    return nullptr;
}

VoxEng::ShaderLayout::ShaderLayout(std::vector<ShaderLayoutLocation> elements) : elements(elements) {}

VoxEng::ShaderLayout::ShaderLayout(const std::initializer_list<ShaderLayoutLocation> elements) : elements(elements) {}
