#pragma once

#include "pch.h"
#include <Core/Rendering/Shader.h>

class LightSource
{
public:
    LightSource(glm::vec3 color, glm::vec2 intensity);

    virtual void Use(const std::string& uniform, Shader& shader);
protected:
    glm::vec3 m_color;
    glm::vec2 m_intensity;
};
