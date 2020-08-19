//
// Created by Gerry on 2020-08-17.
//

#ifndef CPPMC_SHADER_H
#define CPPMC_SHADER_H

#include <core/Core.h>
#include <string>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
namespace VoxEng {
    class Shader {
    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void setAttribLocation(std::vector<std::string> locations) = 0;
        virtual void setUniform(const std::string& name, int value) = 0;
        virtual void setUniform(const std::string& name, float value) = 0;
        virtual void setUniform(const std::string& name, bool value) = 0;
        virtual void setUniform(const std::string& name, const glm::mat4& value) = 0;
        virtual void setUniform(const std::string& name, const glm::vec2& value) = 0;
        virtual void setUniform(const std::string& name, const glm::vec3& value) = 0;
        virtual void setUniform(const std::string& name, const glm::vec4& value) = 0;
        static Ref <Shader> create(const std::string& vertex, const std::string& fragment);
        virtual ~Shader() = default;
    };
}
#endif //CPPMC_SHADER_H
