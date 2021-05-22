//
// Created by Gerry on 2020-08-17.
//

#ifndef CPPMC_OPENGLSHADER_H
#define CPPMC_OPENGLSHADER_H

#include <string>
#include <map>
#include <core/graphics/Shader.h>

namespace Ziti {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const ShaderData& shader,ShaderLayout& layout);

        void bind() override;

        void unbind() override;

        void setUniform(const std::string &name, int value) override;

        void setUniform(const std::string &name, float value) override;

        void setUniform(const std::string &name, bool value) override;

        void setUniform(const std::string &name, const glm::vec4& value) override;

        void setUniform(const std::string &name, const glm::mat4& value) override;

        void setUniform(const std::string &name, const glm::vec2& value) override;

        void setUniform(const std::string &name, const glm::vec3& value) override;

        ~OpenGLShader() override;

    private:
        unsigned int getUniformLocation(const std::string& uniformName);
        unsigned int compileShader(unsigned int shaderType, const std::string& src);

        unsigned int _program;
        std::map<std::string,unsigned int> _uniformLocations;
        static unsigned int _sBoundProgram;
    };
}


#endif //CPPMC_OPENGLSHADER_H
