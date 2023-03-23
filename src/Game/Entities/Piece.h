#pragma once

#include "pch.h"
#include <Core/Rendering/GameObject.h>

enum Color
{
    White, Black
};

class Piece : public GameObject
{
protected:
    Color m_color;

    Piece(std::shared_ptr<Renderable>& model, Color color, glm::vec3 position = glm::vec3());
    Piece(std::shared_ptr<Renderable>& model, Color color, glm::mat4 transform);
};

