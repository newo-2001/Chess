#pragma once

#include "pch.h"
#include "Shader.h"

class Material
{
public:
    Material(float specularIntensity, float shininess);

    void Use(Shader& shader);
private:
    float m_specularIntensity, m_shininess;
};

