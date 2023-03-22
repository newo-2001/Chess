#pragma once

#include "pch.h"
#include "Shader.h"

class Material
{
public:
    Material(float specularIntensity, float shininess, glm::vec3 color = glm::vec3(1.0f));

    void Use(Shader& shader);
private:
    glm::vec3 m_color;
    float m_specularIntensity, m_shininess;
};

