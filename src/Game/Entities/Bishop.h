#pragma once

#include "pch.h"
#include "Piece.h"

class Bishop : public Piece
{
public:
    Bishop(Color color, glm::vec3 position = glm::vec3());
};

