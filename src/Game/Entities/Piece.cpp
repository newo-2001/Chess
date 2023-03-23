#include "pch.h"
#include "Piece.h"
#include <Game/Libraries/Materials.h>

//glm::mat4 initialTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.002f));

Piece::Piece(std::shared_ptr<Renderable>& model, Color color, glm::vec3 position) :
    Piece(model, color, glm::translate(glm::mat4(1.0f), position))
{ }

Piece::Piece(std::shared_ptr<Renderable>& model, Color color, glm::mat4 transform) :
    GameObject(model, glm::scale(transform, glm::vec3(0.002f)), nullptr,
               color == White ? Materials::White : Materials::Black),
    m_color(color)
{ }

void Piece::SetTransform(glm::mat4 transform)
{
    GameObject::SetTransform(glm::scale(transform, glm::vec3(0.002f)));
}
