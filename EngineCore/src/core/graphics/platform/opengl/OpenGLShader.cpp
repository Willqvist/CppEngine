//
// Created by Gerry on 2020-08-17.
//

#include <glad/glad.h>
#include "OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"

unsigned int Ziti::OpenGLShader::_sBoundProgram = -1;

Ziti::OpenGLShader::OpenGLShader(const ShaderData& shader, ShaderLayout& layout): _program(glCreateProgram())  {

    unsigned int vs = compileShader(GL_VERTEX_SHADER, shader.vertex);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, shader.fragment);

    for(const ShaderLayoutLocation& location : layout._elements) {
        glBindAttribLocation(_program,location._location,location._name.c_str());
    }

    glAttachShader(_program, vs);
    glAttachShader(_program, fs);
    glLinkProgram(_program);
    glValidateProgram(_program);

    #ifndef DEBUG_ENABLE
        glDetachShader(_program,vs);
        glDetachShader(_program,fs);
    #endif

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Ziti::OpenGLShader::bind() {
    if(_sBoundProgram == _program) return;
    _sBoundProgram = _program;
    glUseProgram(_program);
}

void Ziti::OpenGLShader::unbind() {
    _sBoundProgram = -1;
    glUseProgram(0);
}

Ziti::OpenGLShader::~OpenGLShader() {
    glDeleteProgram(_program);
}

unsigned int Ziti::OpenGLShader::compileShader(unsigned int shaderType, const std::string &src) {
    unsigned int id = glCreateShader(shaderType);
    const char* srcChar = src.c_str();
    glShaderSource(id, 1, &srcChar,nullptr);
    glCompileShader(id);
    int res;
#ifdef DEBUG_ENABLE
    glGetShaderiv(id, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        fprintf(stderr,"Failed to compile [%s]: %s",shaderType==GL_VERTEX_SHADER?"Vertex":"Fragment",message);
    }
#endif
    return id;
}

void Ziti::OpenGLShader::setUniform(const std::string &name, int value) {

}

void Ziti::OpenGLShader::setUniform(const std::string &name, float value) {
    //fprintf(stderr,"BINDING: %s with value: %d", name.c_str(), value);
    glUniform1f(getUniformLocation(name),value);
}

void Ziti::OpenGLShader::setUniform(const std::string &name, bool value) {
    glUniform1i(getUniformLocation(name),value);
}

void Ziti::OpenGLShader::setUniform(const std::string &name, const glm::mat4& value) {
    glUniformMatrix4fv(getUniformLocation(name),1,GL_FALSE,value_ptr(value));
}

void Ziti::OpenGLShader::setUniform(const std::string &name, const glm::vec2& value) {
    glUniform2fv(getUniformLocation(name),1,value_ptr(value));
}

void Ziti::OpenGLShader::setUniform(const std::string &name, const glm::vec3& value) {
    glUniform3fv(getUniformLocation(name),1,value_ptr(value));
}

void Ziti::OpenGLShader::setUniform(const std::string &name, const glm::vec4& value) {
    glUniform4fv(getUniformLocation(name),1,value_ptr(value));
}

unsigned int Ziti::OpenGLShader::getUniformLocation(const std::string &uniformName) {
    if(_uniformLocations.find(uniformName) != _uniformLocations.end()) {
        return _uniformLocations[uniformName];
    }
    unsigned int val = glGetUniformLocation(_program, uniformName.c_str());
    _uniformLocations[uniformName] = val;
    return val;
}

