//
// Created by Gerry on 2020-08-17.
//

#include "Material.h"
#include "GraphicsLibrary.h"



VoxEng::Material::Material(const VoxEng::Ref<VoxEng::Shader> &shader) {
    this->shader = shader;
    this->visit.shader = shader;
    this->id = globalId ++;
}

void VoxEng::Material::bind() {
    if(boundMaterial == id) return;
    shader->bind();
    for(MaterialVariable& variable : variables) {
        this->visit.name = variable.name;
        std::visit(this->visit,variable.value);
    }
}

void VoxEng::Material::unbind() {
    shader->unbind();
}
/*
void VoxEng::Material::set(const std::string &name, float value) {
    variables.push_back({name,value});
}

void VoxEng::Material::set(const std::string &name, int value) {
    variables.push_back({name,value});
}

void VoxEng::Material::set(const std::string &name, bool value) {
    variables.push_back({name,value});
}

void VoxEng::Material::set(const std::string &name, const glm::vec2 &value) {
    variables.push_back({name,value});
}

void VoxEng::Material::set(const std::string &name, const glm::vec3 &value) {
    variables.push_back({name,value});
}

void VoxEng::Material::set(const std::string &name, const glm::vec4 &value) {
    variables.push_back({name,value});
}
void VoxEng::Material::set(const std::string &name, const glm::mat4 &value) {
    if(alreadySet(name,value))
        return;
    variables.push_back({name,value});
}
*/
void VoxEng::Material::set(const std::string &name, const VoxEng::Ref<VoxEng::Texture> &value) {
    textures.push_back(value);
}

VoxEng::Ref<VoxEng::Material> VoxEng::Material::create(const VoxEng::Ref<VoxEng::Shader> &shader) {
    return CreateRef<Material>(shader);
}

VoxEng::MaterialVariable *VoxEng::Material::get(const std::string &name) {
    int index = 0;
    for(MaterialVariable& variable: variables)
    {
        if(variable.name == name) {
            MaterialVariable* val = variables.data();
            return (val+index);
        }
        index ++;
    }
    return nullptr;
}

void VoxEng::Material::set(const std::string &name, VoxEng::MaterialTypes value) {
    if(boundMaterial == id)
        boundMaterial = -1;

    MaterialVariable* var = get(name);
    if(var) {
        var->value = value;
        return;
    }
    variables.push_back({name,value});
}

VoxEng::Ref<VoxEng::Shader> &VoxEng::Material::getShader() {
    return shader;
}


