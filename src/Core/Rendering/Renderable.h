#pragma once
#include "pch.h"
#include "Shader.h"

class Renderable
{
public:
    virtual void Render(Shader& shader) = 0;
};
