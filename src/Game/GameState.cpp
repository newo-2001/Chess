#include "pch.h"
#include "GameState.h"
#include "Game.h"
#include <Core/Debug/Logging.h>


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
    // If right mouse was clicked, remove selection
    if (event.button == GLFW_MOUSE_BUTTON_RIGHT && event.action == GLFW_PRESS)
    {
        m_selectedSquare = std::nullopt;
        return;
    // Event was not left mouse press, not interested
    } else if (event.action != GLFW_PRESS || event.button != GLFW_MOUSE_BUTTON_LEFT)
    {
        return;
    }

    // Cast ray to the clickd tile
    Ray ray = Game::GetActiveScene().GetCamera().CastMouseRay();
    std::optional<glm::vec3> result = ray.Intersect(m_board->GetHitBox());

    // Ray missed, no square was clicked
    if (!result.has_value())
    {
        m_selectedSquare = std::nullopt;
        return;
    }
    
    // Calculate tile position from world position
    glm::vec3 location = glm::floor(result.value());
    glm::ivec2 target = glm::ivec2(location.z, location.x) + glm::ivec2(4);
    std::cout << target << std::endl;

    // If no square was selected, selected the clicked square
    if (!m_selectedSquare)
    {
        // You can't select an empty tile to move from
        // Piece has to be your own color
        std::unique_ptr<Piece>& piece = m_board->PieceAt(target);
        if (!piece || piece->GetColor() != m_playerColor)
        {
            return;
        }

        m_selectedSquare = target;
        return;
    // If the currently selected square was clicked, deselect it
    } else if (glm::all(glm::equal(m_selectedSquare.value(), target)))
    {
        m_selectedSquare = std::nullopt;
        return;
    }
    
    try
    {
        // Attempt to perform the move
        m_board->MovePiece(m_selectedSquare.value(), target);
    }
    catch (std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
    }

    m_selectedSquare = std::nullopt;
}
