#pragma once

#include "pch.h"

#include <Core/Events/Events.h>
#include <Core/Events/EventTopic.h>

class InputHandler
{
public:
    InputHandler();
    bool IsKeyPressed(int key) const { return m_pressedKeys[key]; }
    bool IsButtonPressed(int button) const { return m_pressedButtons[button]; }
    glm::ivec2 GetMousePosition() const { return m_mousePosition; }

    void ReleaseAll();

    EventTopic<KeyEvent> OnKeyEvent;
    EventTopic<MouseButtonEvent> OnMouseButtonEvent;
    EventTopic<MouseMoveEvent> OnMouseMoveEvent;
    EventTopic<glm::vec2> OnMouseScrollEvent;
private:
    std::array<bool, 1024> m_pressedKeys = { false };
    std::array<bool, 24> m_pressedButtons = { false };
    glm::ivec2 m_mousePosition = glm::ivec2();
};