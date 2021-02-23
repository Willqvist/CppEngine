//
// Created by Gerry on 2020-08-17.
//

#ifndef CPPMC_OPENGLSHADER_H
#define CPPMC_OPENGLSHADER_H

#include <rendering/Shader.h>
#include <string>
#include <map>

namespace VoxEng {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& vertex,const std::string& fragment,ShaderLayout& layout);

        void bind() override;

        void unbind() override;

        void setUniform(const std::string &name, int value) override;

        void setUniform(const std::string &name, float value) override;

        void setUniform(const std::string &name, bool value) override;

        void setUniform(const std::string &name, const glm::vec4& value) override;

        void setUniform(const std::string &name, const glm::mat4& value) override;

        void setUniform(const std::string &name, const glm::vec2& value) override;

        void setUniform(const std::string &name, const glm::vec3& value) override;

        void setAttribLocation(std::vector<std::string> locations) override;

        ~OpenGLShader() override;

    private:
        unsigned int getUniformLocation(const std::string& uniformName);
        unsigned int program;
        unsigned int compileShader(unsigned int shaderType, const std::string& src);
        std::map<std::string,unsigned int> uniformLocations;
        static inline unsigned int boundProgram = -1;
    };
}


#endif //CPPMC_OPENGLSHADER_H
