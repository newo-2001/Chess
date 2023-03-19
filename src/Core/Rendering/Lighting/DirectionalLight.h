#pragma once

#include "pch.h"
#include "LightSource.h"
#include <Core/Rendering/Shader.h>

class DirectionalLight : public LightSource
{
public:
    DirectionalLight(glm::vec3 color, glm::vec2 intensity, glm::vec3 direction);

    glm::vec3 GetDirection() const { return m_direction; }

    void Use(const std::string& uniform, Shader& shader);
private:
    glm::vec3 m_direction;
};

