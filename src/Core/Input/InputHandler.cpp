#include "pch.h"
#include "InputHandler.h"

void InputHandler::ReleaseAll()
{
    m_pressedKeys.fill(false);
    m_pressedButtons.fill(false);
}