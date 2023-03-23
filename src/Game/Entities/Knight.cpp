#include "pch.h"
#include "Knight.h"
#include <Game/Libraries/Models.h>

Knight::Knight(Color color, glm::vec3 position) :
    Piece(Models::Knight, color, glm::rotate(
        glm::translate(glm::mat4(1.0f), position),
        glm::radians(90.0f) * (color == White ? 1 : -1),
        glm::vec3 { 0.0f, 1.0f, 0.0f }
    ))
{ }

void Knight::SetTransform(glm::mat4 transform)
{
    float angle = glm::radians(90.0f) * (m_color == White ? 1 : -1);
    Piece::SetTransform(glm::rotate(transform, angle, glm::vec3 { 0.0f, 1.0f, 0.0f }));
}
