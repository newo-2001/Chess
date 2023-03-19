#include "pch.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec2 intensity, glm::vec3 direction) :
    LightSource(color, intensity),
    m_direction(glm::normalize(direction))
{ }

void DirectionalLight::Use(const std::string& uniform, Shader& shader)
{
    shader.SetUniform(Uniform<glm::vec3> { uniform + ".direction", m_direction });

    LightSource::Use(uniform + ".base", shader);
}
