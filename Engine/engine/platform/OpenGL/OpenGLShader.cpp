//
// Created by Gerry on 2020-08-17.
//

#include <glad/glad.h>
#include <tools/Tools.h>
#include "OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"

VoxEng::OpenGLShader::OpenGLShader(const std::string &vertex, const std::string& fragment,ShaderLayout& layout): program(glCreateProgram())  {

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertex);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragment);

    for(const ShaderLayoutLocation& location : layout.elements) {
        glBindAttribLocation(program,location.location,location.name.c_str());
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    #ifndef DEBUG_ENABLE
        glDetachShader(program,vs);
        glDetachShader(program,fs);
    #endif

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void VoxEng::OpenGLShader::bind() {
    if(boundProgram == program) return;
    boundProgram = program;
    glUseProgram(program);
}

void VoxEng::OpenGLShader::unbind() {
    boundProgram = -1;
    glUseProgram(0);
}

VoxEng::OpenGLShader::~OpenGLShader() {
    glDeleteProgram(program);
}

unsigned int VoxEng::OpenGLShader::compileShader(unsigned int shaderType, const std::string &src) {
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
        DEBUG_LOG("Failed to compile [%s]: %s",shaderType==GL_VERTEX_SHADER?"Vertex":"Fragment",message);
    }
#endif
    return id;
}

void VoxEng::OpenGLShader::setUniform(const std::string &name, int value) {

}

void VoxEng::OpenGLShader::setUniform(const std::string &name, float value) {
    //DEBUG_LOG("BINDING: %s with value: %d", name.c_str(), value);
    glUniform1f(getUniformLocation(name),value);
}

void VoxEng::OpenGLShader::setUniform(const std::string &name, bool value) {
    glUniform1i(getUniformLocation(name),value);
}

void VoxEng::OpenGLShader::setUniform(const std::string &name, const glm::mat4& value) {
    glUniformMatrix4fv(getUniformLocation(name),1,GL_FALSE,value_ptr(value));
}

void VoxEng::OpenGLShader::setUniform(const std::string &name, const glm::vec2& value) {
    glUniform2fv(getUniformLocation(name),1,value_ptr(value));
}

void VoxEng::OpenGLShader::setUniform(const std::string &name, const glm::vec3& value) {
    glUniform3fv(getUniformLocation(name),1,value_ptr(value));
}

void VoxEng::OpenGLShader::setUniform(const std::string &name, const glm::vec4& value) {
    glUniform4fv(getUniformLocation(name),1,value_ptr(value));
}

unsigned int VoxEng::OpenGLShader::getUniformLocation(const std::string &uniformName) {
    if(uniformLocations.find(uniformName) != uniformLocations.end()) {
        return uniformLocations[uniformName];
    }
    unsigned int val = glGetUniformLocation(program, uniformName.c_str());
    uniformLocations[uniformName] = val;
    return val;
}

void VoxEng::OpenGLShader::setAttribLocation(std::vector<std::string> locations) {
    bind();
    int i = 0;
    for(const std::string& str : locations) {
        glBindAttribLocation(program,i,str.c_str());
        i++;
    }
}

