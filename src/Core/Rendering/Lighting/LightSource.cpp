#include "pch.h"
#include "LightSource.h"

LightSource::LightSource(glm::vec3 color, glm::vec2 intensity) :
    m_color(color),
    m_intensity(intensity)
{ }

void LightSource::Use(const std::string& uniform, Shader& shader)
{
    shader.SetUniform(Uniform<glm::vec3> { uniform + ".color", m_color });
    shader.SetUniform(Uniform<float> { uniform + ".ambientIntensity", m_intensity.x });
    shader.SetUniform(Uniform<float> { uniform + ".diffuseIntensity", m_intensity.y });
}
