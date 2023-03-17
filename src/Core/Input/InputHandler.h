#pragma once

#include "pch.h"

#include <Core/Events/Events.h>
#include <Core/Events/EventTopic.h>

class InputHandler
{
public:
    bool IsKeyPressed(int key) const { return m_pressedKeys[key]; }
    bool IsButtonPressed(int button) const { return m_pressedButtons[button]; }

    void ReleaseAll();

    EventTopic<KeyEvent> OnKeyEvent;
    EventTopic<MouseButtonEvent> OnMouseButtonEvent;
    EventTopic<MouseMoveEvent> OnMouseMoveEvent;
private:
    std::array<bool, 1024> m_pressedKeys = { false };
    std::array<bool, 24> m_pressedButtons = { false };
};