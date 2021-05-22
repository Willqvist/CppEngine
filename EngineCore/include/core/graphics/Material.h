//
// Created by Gerry on 2020-08-17.
//

#ifndef CPPMC_MATERIAL_H
#define CPPMC_MATERIAL_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <map>
#include <list>
#include <variant>
#include <vector>
#include <glm/mat4x4.hpp>
#include <string>
#include <core/graphics/Shader.h>
namespace Ziti {
    class Texture;
    typedef std::variant<float,int,bool,glm::vec2,glm::vec3,glm::vec4,glm::mat4> MaterialTypes;

    struct MaterialTexture {
        std::string name;
        Ref<Texture> texture;
    };

    struct MaterialVariable {
        std::string name;
        MaterialTypes value;
    };


    struct VisitShader {
        Ziti::Ref<Shader> shader;
        std::string name;

        void operator()(int& val) {
            shader->setUniform(name,val);
        };
        void operator()(float& val) {
            shader->setUniform(name,val);
        };
        void operator()(bool& val) {
            shader->setUniform(name,val);
        };
        void operator()(glm::vec2& val) {
            shader->setUniform(name,val);
        };
        void operator()(glm::vec3& val) {
            shader->setUniform(name,val);
        };
        void operator()(glm::vec4& val) {
            shader->setUniform(name,val);
        };
        void operator()(glm::mat4& val) {
            shader->setUniform(name,val);
        };
    };

    class Material {
    public:
        Material(const Ref<Shader>& shader);

        void bind();
        void unbind();
        /*
        void set(const std::string& name, float value);
        void set(const std::string& name, int value);
        void set(const std::string& name, bool value);
        void set(const std::string& name, const glm::vec2& value);
        void set(const std::string& name, const glm::vec3& value);
        void set(const std::string& name, const glm::vec4& value);
        void set(const std::string& name, const glm::mat4& value);
        */
        void set(const std::string& name, const Ref<Texture>& value);
        void set(const std::string& name, MaterialTypes value);

        Ref<Shader>& getShader();

        static Ref<Material> create(const Ref<Shader>& shader);
        ~Material() = default;
    private:
        MaterialVariable* get(const std::string& name);

        unsigned int _id;
        Ref<Shader> _shader;
        std::vector<MaterialTexture> _textures;
        std::vector<MaterialVariable> _variables;
        VisitShader _visit;
        static unsigned int _sBoundMaterial;
        static unsigned int _sGlobalId;

    };
}


#endif //CPPMC_MATERIAL_H
