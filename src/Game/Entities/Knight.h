#pragma once

#include "pch.h"
#include "Piece.h"

class Knight : public Piece
{
public:
    Knight(Color color, glm::vec3 position = glm::vec3());
    
    void SetTransform(glm::mat4 transform);
};

