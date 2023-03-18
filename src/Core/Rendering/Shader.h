#pragma once

#include "pch.h"

template<typename T>
struct Uniform
{
    std::string Name;
    T Value;
};

class Shader
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Validate() const;

    void Bind() const;
    static void Unbind();

    template <typename T>
    void SetUniform(Uniform<T> uniform);
private:
    std::unordered_map<std::string, GLint> m_uniformCache;
    GLuint m_program;

    GLint GetUniformLocation(const std::string& name);
    void AttachShader(GLenum shaderType, const std::string& path);

    void VerifyProgramStatus(GLenum status) const;
};
