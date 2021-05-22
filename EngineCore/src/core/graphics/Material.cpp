//
// Created by Gerry on 2020-08-17.
//

#include <core/graphics/Shader.h>
#include "core/graphics/Material.h"
#include <core/graphics/Texture.h>

unsigned int Ziti::Material::_sBoundMaterial = -1;
unsigned int Ziti::Material::_sGlobalId = 0;

Ziti::Material::Material(const Ziti::Ref<Ziti::Shader> &shader) {
    this->_shader = shader;
    this->_visit.shader = shader;
    this->_id = _sGlobalId ++;
}

void Ziti::Material::bind() {
    if(_sBoundMaterial == _id) return;
    _shader->bind();
    for(MaterialVariable& variable : _variables) {
        this->_visit.name = variable.name;
        std::visit(this->_visit, variable.value);
    }

    //TODO: change so texture can bind and unbind when finished, not overiding texture slots every bind!.
    int loc = 0;
    for(MaterialTexture& tex : _textures) {
        tex.texture->activate(loc);
        _shader->setUniform(tex.name, loc);
        loc ++;
    }
}

void Ziti::Material::unbind() {
    _shader->unbind();
}
/*
void Ziti::Material::set(const std::string &name, float value) {
    variables.push_back({name,value});
}

void Ziti::Material::set(const std::string &name, int value) {
    variables.push_back({name,value});
}

void Ziti::Material::set(const std::string &name, bool value) {
    variables.push_back({name,value});
}

void Ziti::Material::set(const std::string &name, const glm::vec2 &value) {
    variables.push_back({name,value});
}

void Ziti::Material::set(const std::string &name, const glm::vec3 &value) {
    variables.push_back({name,value});
}

void Ziti::Material::set(const std::string &name, const glm::vec4 &value) {
    variables.push_back({name,value});
}
void Ziti::Material::set(const std::string &name, const glm::mat4 &value) {
    if(alreadySet(name,value))
        return;
    variables.push_back({name,value});
}
*/
void Ziti::Material::set(const std::string &name, const Ziti::Ref<Ziti::Texture> &value) {
    _textures.push_back({name, value});
}

Ziti::Ref<Ziti::Material> Ziti::Material::create(const Ziti::Ref<Ziti::Shader> &shader) {
    return CreateRef<Material>(shader);
}

Ziti::MaterialVariable *Ziti::Material::get(const std::string &name) {
    int index = 0;
    for(MaterialVariable& variable: _variables)
    {
        if(variable.name == name) {
            MaterialVariable* val = _variables.data();
            return (val+index);
        }
        index ++;
    }
    return nullptr;
}

void Ziti::Material::set(const std::string &name, Ziti::MaterialTypes value) {
    if(_sBoundMaterial == _id)
        _sBoundMaterial = -1;

    MaterialVariable* var = get(name);
    if(var) {
        var->value = value;
        return;
    }
    _variables.push_back({name, value});
}

Ziti::Ref<Ziti::Shader> &Ziti::Material::getShader() {
    return _shader;
}


