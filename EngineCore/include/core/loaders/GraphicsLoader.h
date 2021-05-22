//
// Created by Gerry on 2021-05-09.
//

#ifndef CPPMC_GRAPHICSLOADER_H
#define CPPMC_GRAPHICSLOADER_H

#include <core/graphics/Shader.h>
#include <core/graphics/Texture.h>
namespace Ziti {

    class GraphicsLoader {
    public:
        static Ref<Shader> loadShader(const std::string& path);
        static Ref<Texture> loadTexture(const std::string& path);
    private:
        static ShaderData parseShaderFile(const std::string& path);
    };
}


#endif //CPPMC_GRAPHICSLOADER_H
