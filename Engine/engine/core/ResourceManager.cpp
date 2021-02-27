//
// Created by Gerry on 2020-08-13.
//

#include <tools/Tools.h>
#include "ResourceManager.h"

VoxEng::Ref<VoxEng::Texture>
VoxEng::ResourceManager::loadTexture(const std::string& path, const VoxEng::TextureDetails &details) {
    if(textures.find(path) != textures.end()) {
        return textures[path];
    }
    Ref<Texture> tex = Texture::create(path.c_str(), details);
    textures[path] = tex;
    return tex;
}

VoxEng::Ref<VoxEng::Texture> VoxEng::ResourceManager::loadTexture(const std::string &path) {
    return ResourceManager::loadTexture(path, Texture::defaultDetails);
}

VoxEng::Ref<VoxEng::Shader> VoxEng::ResourceManager::loadShader(const std::string &path, ShaderLayout& layout) {
    //TODO: cache loaded shaders;
    ParsedShader parsedShaders;
    if(!loadShaders(path.c_str(), &parsedShaders)) {
        DEBUG_ERROR("Could not find shader: %s",path.c_str());
        exit(1);
    }
    Ref<Shader> s = Shader::create(parsedShaders.vertex,parsedShaders.fragment,layout);
    s->setAttribLocation(parsedShaders.in);
    return s;
}

VoxEng::Ref<VoxEng::Shader> VoxEng::ResourceManager::loadShader(const std::string &path) {
    //TODO: cache loaded shaders;
    ParsedShader parsedShaders;
    if(!loadShaders(path.c_str(), &parsedShaders)) {
        DEBUG_ERROR("Could not find shader: %s",path.c_str());
        exit(100);
    }
    std::vector<ShaderLayoutLocation> locations;
    for(int i = 0; i < parsedShaders.in.size(); i++) {
        locations.push_back({parsedShaders.in[i],i});
    }
    ShaderLayout layout = ShaderLayout(locations);

    Ref<Shader> s = Shader::create(parsedShaders.vertex,parsedShaders.fragment,layout);
    s->setAttribLocation(parsedShaders.in);
    return s;
}

VoxEng::Ref<VoxEng::Material> VoxEng::ResourceManager::createMaterial(const std::string &name, const Ref<Shader>& shader) {
    //TODO: cache created materials by name.
    return Material::create(shader);
}
