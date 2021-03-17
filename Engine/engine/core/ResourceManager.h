//
// Created by Gerry on 2020-08-13.
//

#ifndef CPPMC_RESOURCEMANAGER_H
#define CPPMC_RESOURCEMANAGER_H

#include <vector>
#include <string>
#include <map>
#include "Core.h"

namespace VoxEng {

    class Texture;
    class Shader;
    struct TextureDetails;
    class ShaderLayout;
    class Material;

    class ResourceManager {
    public:
        static Ref <Texture> loadTexture(const std::string& path, const TextureDetails& details);
        static Ref <Texture> loadTexture(const std::string& path);

        static Ref <Shader> loadShader(const std::string& path);
        static Ref <Shader> loadShader(const std::string& path, ShaderLayout& layout);
        static Ref <Material> createMaterial(const std::string& name, const Ref<Shader>& shader);
    private:
        inline static std::map<std::string, Ref<Texture>> textures;
    };
}


#endif //CPPMC_RESOURCEMANAGER_H
