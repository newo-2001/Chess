#include "pch.h"
#include "Material.h"

Material::Material(float specularIntensity, float shininess, glm::vec3 color) :
    m_specularIntensity(specularIntensity),
    m_shininess(shininess),
    m_color(color)
{ }

void Material::Use(Shader& shader)
{
    shader.SetUniform(Uniform<float> { "material.specularIntensity", m_specularIntensity });
    shader.SetUniform(Uniform<float> { "material.shininess", m_shininess });
    shader.SetUniform(Uniform<glm::vec3> { "material.color", m_color });
}
