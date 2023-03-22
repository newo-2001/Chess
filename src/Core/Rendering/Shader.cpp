#include "pch.h"
#include "Shader.h"

#include <fstream>
#include <sstream>

std::string ReadFile(const std::string& path);

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    m_program = glCreateProgram();

    if (!m_program)
    {
        const char* error = (const char*) glewGetErrorString(glGetError());
        throw std::runtime_error(std::format("Failed to create shader program: {}", error));
    }

    try
    {
        AttachShader(GL_VERTEX_SHADER, vertexPath);
        AttachShader(GL_FRAGMENT_SHADER, fragmentPath);
        
        glLinkProgram(m_program);
        VerifyProgramStatus(GL_LINK_STATUS);
    }
    catch (...)
    {
        glDeleteProgram(m_program);
        throw;
    }
}

Shader::~Shader()
{
    glDeleteProgram(m_program);
}

void Shader::Bind() const
{
    glUseProgram(m_program);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::Validate() const
{
    glValidateProgram(m_program);
    VerifyProgramStatus(GL_VALIDATE_STATUS);
}

void CompileShader(GLuint shader, GLenum shaderType)
{
    glCompileShader(shader);
    
    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result) return;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &result);
    std::unique_ptr<GLchar[]> errorLog = std::make_unique<GLchar[]>(result);
    glGetShaderInfoLog(shader, result, NULL, errorLog.get());

    throw std::runtime_error(errorLog.get());
}

void Shader::AttachShader(GLenum shaderType, const std::string& filePath)
{
    const std::string& source = ReadFile(filePath);
    const GLchar* sources[] = { source.c_str() };
    const GLint lengths[] = { (GLint) source.size() };

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, sources, lengths);
    
    try
    {
        CompileShader(shader, shaderType);
    }
    catch (...)
    {
        glDeleteShader(shader);
        std::throw_with_nested(std::runtime_error(std::format("Failed to compile shader '{}'", filePath)));
    }

    glAttachShader(m_program, shader);
    glDeleteShader(shader);
}

void Shader::VerifyProgramStatus(GLenum status) const
{
    GLint result;
    glGetProgramiv(m_program, status, &result);
    if (result) return;

    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &result);
    std::unique_ptr<GLchar[]> errorLog = std::make_unique<GLchar[]>(result);
    glGetProgramInfoLog(m_program, result, NULL, errorLog.get());

    throw std::runtime_error(std::format("Shader program verification failed: {}", errorLog.get()));
}

std::string ReadFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error(std::format("Failed to read file: {}", path));
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLint Shader::GetUniformLocation(const std::string& name)
{
    auto it = m_uniformCache.find(name);

    if (it != m_uniformCache.end())
    {
        return (*it).second;
    }

    GLint location = glGetUniformLocation(m_program, name.c_str());
    if (location == -1)
    {
        std::cout << "[WARNING] Invalid Uniform: " + name << std::endl;
    }

    m_uniformCache.insert({ name, location });
    return location;
}

template<>
void Shader::SetUniform<glm::mat4>(Uniform<glm::mat4> uniform)
{
    GLint location = GetUniformLocation(uniform.Name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(uniform.Value));
}

template<>
void Shader::SetUniform<glm::vec3>(Uniform<glm::vec3> uniform)
{
    GLint location = GetUniformLocation(uniform.Name);
    glUniform3fv(location, 1, glm::value_ptr(uniform.Value));
}

template<>
void Shader::SetUniform<float>(Uniform<float> uniform)
{
    GLint location = GetUniformLocation(uniform.Name);
    glUniform1f(location, uniform.Value);
}

template<>
void Shader::SetUniform<int>(Uniform<int> uniform)
{
    GLint location = GetUniformLocation(uniform.Name);
    glUniform1i(location, uniform.Value);
}
