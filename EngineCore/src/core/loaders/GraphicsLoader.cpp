//
// Created by Gerry on 2021-05-09.
//

#include <core/graphics/GraphicsCore.h>
#include "core/loaders/GraphicsLoader.h"
#include <fstream>
#include <core/utils/ATFileParser.h>

Ziti::Ref<Ziti::Shader> Ziti::GraphicsLoader::loadShader(const std::string &path) {
    //TODO: cache values!
    ShaderData data = parseShaderFile(path);

    if(data.vertex.empty() && data.fragment.empty()  && data.geometry.empty())
        return nullptr;

    return Shader::create(data);
}

Ziti::Ref <Ziti::Texture> Ziti::GraphicsLoader::loadTexture(const std::string &path) {
    return Texture::create(path);
}

Ziti::ShaderData Ziti::GraphicsLoader::parseShaderFile(const std::string &path) {
    ATFileReader reader(path);
    ShaderData data;

    int state = 0;

    reader.addAttrListener("begin",[&](ATFileReader* reader, std::string& value, std::string& contents) {
        if(value == "vertex") {
            state = 1;
        }
        if(value == "fragment") {
            state = 2;
        }
    });

    reader.addAttrListener("end",[&](ATFileReader* reader, std::string value, std::string& contents) {
        if(state == 1) {
            data.vertex = contents;
        }
        if(state == 2) {
            data.fragment = contents;
        }
        state = 0;
    });

    reader.read();
    return data;
}

