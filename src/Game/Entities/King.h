#pragma once

#include "pch.h"
#include "Piece.h"

class King : public Piece
{
public:
    King(Color color, glm::vec3 position = glm::vec3());
};

