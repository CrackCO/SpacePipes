#include "Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cstdlib>


Shader::Shader() : program(0) {}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::bind() const
{
    glUseProgram(program);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::compile()
{
    GLuint vert = compileShader(GL_VERTEX_SHADER,   vertSrc);
    GLuint frag = compileShader(GL_FRAGMENT_SHADER, fragSrc);

    program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    glDeleteShader(vert);
    glDeleteShader(frag);
}


GLuint Shader::compileShader(GLuint type, const char* src)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);

    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
    }

    return shader;
}



void Shader::setBool(const std::string& name, bool val) const
{
    GLint loc = glGetUniformLocation(program, name.c_str());
    if (loc != -1) glUniform1i(loc, static_cast<int>(val));
}

void Shader::setInt(const std::string& name, int val) const
{
    GLint loc = glGetUniformLocation(program, name.c_str());
    if (loc != -1) glUniform1i(loc, val);
}

void Shader::setFloat(const std::string& name, float val) const
{
    GLint loc = glGetUniformLocation(program, name.c_str());
    if (loc != -1) glUniform1f(loc, val);
}

void Shader::setVec2(const std::string& name, const glm::vec2& val) const
{
    GLint loc = glGetUniformLocation(program, name.c_str());
    if (loc != -1) glUniform2fv(loc, 1, glm::value_ptr(val));
}

void Shader::setVec3(const std::string& name, const glm::vec3& val) const
{
    GLint loc = glGetUniformLocation(program, name.c_str());
    if (loc != -1) glUniform3fv(loc, 1, glm::value_ptr(val));
}

void Shader::setVec4(const std::string& name, const glm::vec4& val) const
{
    GLint loc = glGetUniformLocation(program, name.c_str());
    if (loc != -1) glUniform4fv(loc, 1, glm::value_ptr(val));
}

void Shader::setMat2(const std::string& name, const glm::mat2& val) const
{
    GLint loc = glGetUniformLocation(program, name.c_str());
    if (loc != -1) glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setMat3(const std::string& name, const glm::mat3& val) const
{
    GLint loc = glGetUniformLocation(program, name.c_str());
    if (loc != -1) glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setMat4(const std::string& name, const glm::mat4& val) const
{
    GLint loc = glGetUniformLocation(program, name.c_str());
    if (loc != -1) glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}
