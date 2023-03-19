#include "pch.h"
#include "InputHandler.h"

InputHandler::InputHandler()
{
    OnKeyEvent.Subscribe([this](KeyEvent event) -> void
    {
        if (event.action == GLFW_PRESS)
        {
            m_pressedKeys[event.key] = true;
        }
        else if (event.action == GLFW_RELEASE)
        {
            m_pressedKeys[event.key] = false;
        }
    });

    OnMouseButtonEvent.Subscribe([this](MouseButtonEvent event) -> void
    {
        if (event.action == GLFW_PRESS)
        {
            m_pressedKeys[event.button] = true;
        }
        else if (event.action == GLFW_RELEASE)
        {
            m_pressedKeys[event.button] = false;
        }
    });

}

void InputHandler::ReleaseAll()
{
    m_pressedKeys.fill(false);
    m_pressedButtons.fill(false);
}