#include "pch.h"
#include "Piece.h"
#include <Game/Libraries/Materials.h>

glm::mat4 initialTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.002f));

Piece::Piece(std::shared_ptr<Renderable>& model, Color color, glm::vec3 position) :
    GameObject(model, glm::translate(initialTransform, position), nullptr,
               color == White ? Materials::White : Materials::Black),
    m_color(color)
{ }
