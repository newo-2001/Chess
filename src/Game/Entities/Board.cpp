#include "pch.h"
#include "Board.h"
#include <Game/Materials.h>

Board::Board(glm::vec3 position) :
    GameObject(s_model, glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.05f)), position), nullptr, Materials::Shiny)
{ }

void Board::Load()
{
    s_model = std::make_shared<Model>("resources/models/board/Board.obj");
}
