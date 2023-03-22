#pragma once

#include "pch.h"
#include "Piece.h"

class Queen : public Piece
{
public:
    Queen(Color color, glm::vec3 position = glm::vec3());
};

