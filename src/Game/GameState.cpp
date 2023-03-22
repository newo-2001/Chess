#include "pch.h"
#include "GameState.h"
#include "Game.h"

GameState::GameState(std::shared_ptr<Board> board) :
    m_board(board)
{
    InputHandler& inputHandler = Game::GetWindow().GetInputHandler();
    m_mouseButtonEventSubscription = inputHandler.OnMouseButtonEvent.Subscribe([this](MouseButtonEvent event) -> void
    {
        OnMouseButtonEvent(event);
    });
}

void GameState::OnMouseButtonEvent(MouseButtonEvent event)
{
    if (event.button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        m_selectedSquare = std::nullopt;
        return;
    }
    else if (event.button == GLFW_MOUSE_BUTTON_LEFT)
    {
        Ray ray = Game::GetActiveScene().GetCamera().CastMouseRay();

        std::optional<glm::vec3> result = ray.Intersect(m_board->GetHitBox());
        if (!result.has_value())
        {
            m_selectedSquare = std::nullopt;
        }
        else
        {
            glm::vec3 location = glm::floor(result.value());
            m_selectedSquare = glm::ivec2(location.x, location.z) + glm::ivec2(4);
        }
    }
}
