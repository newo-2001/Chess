#pragma once

#include "pch.h"
#include <Core/Rendering/Model.h>
#include <Core/Rendering/GameObject.h>
#include <Core/Physics/Geometry/FinitePlane.h>
#include "Piece.h"

class Board : public GameObject
{
public:
    const static size_t SIZE = 8;

    Board(glm::vec3 position = glm::vec3());

    void Render(Shader& shader) const;
    void MovePiece(glm::ivec2 from, glm::ivec2 to);

    FinitePlane GetHitBox() const { return m_hitBox; }

    std::unique_ptr<Piece>& PieceAt(glm::ivec2 pos) { return m_pieces[pos.x][pos.y]; }
    const std::unique_ptr<Piece>& PieceAt(glm::ivec2 pos) const { return m_pieces[pos.x][pos.y]; }
private:
    FinitePlane m_hitBox;
    std::unique_ptr<GameObject> m_hitBoxObject;

    std::array<std::array<std::unique_ptr<Piece>, SIZE>, SIZE> m_pieces = {};
};
