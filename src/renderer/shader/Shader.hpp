#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    Shader() = default;

    void Bind() const;
    void Unbind() const;

    void Compile();

    void SetBool(const std::string& name, bool val) const;
    void SetInt(const std::string& name, int val) const;
    void SetFloat(const std::string& name, float val) const;
    void SetVec2(const std::string& name, const glm::vec2& val) const;
    void SetVec3(const std::string& name, const glm::vec3& val) const;
    void SetVec4(const std::string& name, const glm::vec4& val) const;
    void SetMat2(const std::string& name, const glm::mat2& val) const;
    void SetMat3(const std::string& name, const glm::mat3& val) const;
    void SetMat4(const std::string& name, const glm::mat4& val) const;

    ~Shader();

private:
    GLuint CompileShader(GLuint type, const char* src);

private:
    static std::string vertSrc;
    static std::string fragSrc;
    GLuint program = 0;
};
