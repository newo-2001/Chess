#pragma once

#include "pch.h"
#include "Entities/Board.h"
#include <Core/Events/Events.h>

class GameState
{
public:
    GameState(std::shared_ptr<Board> board);

    std::optional<glm::ivec2> GetSelectedSquare() const { return m_selectedSquare; };
private:
    std::shared_ptr<Board> m_board;
    std::optional<glm::ivec2> m_selectedSquare = std::nullopt;

    void OnMouseButtonEvent(MouseButtonEvent event);
    
    long m_mouseButtonEventSubscription;
};

