#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
    Pawn(Color color, glm::vec3 position = glm::vec3());
};

