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

    template<typename T>
    void PlacePiece(Color color, glm::ivec2 pos);

    glm::vec3 GetPosition() const { return m_position; }

    void SetStartingPosition();

    FinitePlane GetHitBox() const { return m_hitBox; }

    std::unique_ptr<Piece>& PieceAt(glm::ivec2 pos) { return m_pieces[pos.y][pos.x]; }
    const std::unique_ptr<Piece>& PieceAt(glm::ivec2 pos) const { return m_pieces[pos.y][pos.x]; }
private:
    FinitePlane m_hitBox;
    std::unique_ptr<GameObject> m_hitBoxObject;
    glm::vec3 m_position;

    std::array<std::array<std::unique_ptr<Piece>, SIZE>, SIZE> m_pieces = {};

    glm::vec3 ToWorld(glm::vec2 local) const;
    glm::vec3 ToWorld(glm::ivec2 local) const { return ToWorld(glm::vec2(local)); }
};
