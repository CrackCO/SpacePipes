#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
private:
    static const char* vertSrc;
    static const char* fragSrc;
    GLuint program;

public:
    Shader();
    ~Shader();

    void bind() const;
    void unbind() const;

    void compile();

private:
    GLuint compileShader(GLuint type, const char* src);

public:
    void setBool  (const std::string& name, bool             val) const;
    void setInt   (const std::string& name, int              val) const;
    void setFloat (const std::string& name, float            val) const;
    void setVec2  (const std::string& name, const glm::vec2& val) const;
    void setVec3  (const std::string& name, const glm::vec3& val) const;
    void setVec4  (const std::string& name, const glm::vec4& val) const;
    void setMec4  (const std::string& name, const glm::vec4& val) const;
    void setMat2  (const std::string& name, const glm::mat2& val) const;
    void setMat3  (const std::string& name, const glm::mat3& val) const;
    void setMat4  (const std::string& name, const glm::mat4& val) const;
};