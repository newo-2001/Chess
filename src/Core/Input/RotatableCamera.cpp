#include "pch.h"
#include "RotatableCamera.h"
#include <Game/Game.h>
#include <Core/Time.h>

RotatableCamera::RotatableCamera(glm::vec3 center, float distance, float yaw, float pitch, float fov) :
    m_center(center),
    m_distance(distance),
    Camera(glm::vec3(), yaw, pitch, fov)
{
    InputHandler& inputHandler = Game::GetWindow().GetInputHandler();

    m_mouseMoveEventSubscription = inputHandler.OnMouseMoveEvent.Subscribe([this] (MouseMoveEvent event) -> void
    {
        OnMouseMoveEvent(event.delta);
    });

    m_mouseButtonEventSubscription = inputHandler.OnMouseButtonEvent.Subscribe([this] (MouseButtonEvent event) -> void
    {
        OnMouseButtonEvent(event);
    });

    m_mouseScrollEventSubscription = inputHandler.OnMouseScrollEvent.Subscribe([this] (glm::vec2 event) -> void
    {
        OnMouseScrollEvent(event);
    });

    RecalculatePosition();
}

RotatableCamera::~RotatableCamera()
{
    InputHandler& inputHandler = Game::GetWindow().GetInputHandler();

    inputHandler.OnMouseMoveEvent.Unsubscribe(m_mouseMoveEventSubscription);
    inputHandler.OnMouseButtonEvent.Unsubscribe(m_mouseButtonEventSubscription);
    inputHandler.OnMouseScrollEvent.Unsubscribe(m_mouseScrollEventSubscription);
}

void RotatableCamera::OnMouseMoveEvent(glm::vec2 delta)
{
    Window& window = Game::GetWindow();
    if (!window.CursorIsGrabbed()) return;

    float speed = m_mouseSensitivity * Time::GetDelta();

    constexpr float MAX_ANGLE = glm::radians(85.0f);
    constexpr float MIN_ANGLE = -MAX_ANGLE;

    m_yaw = (float) fmod(m_yaw + delta.x * speed, std::numbers::pi * 2);
    m_pitch = glm::clamp(m_pitch - delta.y * speed, MIN_ANGLE, MAX_ANGLE);

    RecalculatePosition();
}

void RotatableCamera::OnMouseButtonEvent(MouseButtonEvent event)
{
    if (event.button != GLFW_MOUSE_BUTTON_MIDDLE) return;

    Window& window = Game::GetWindow();
    if (event.action == GLFW_PRESS && !window.CursorIsGrabbed())
    {
        window.GrabCursor();
    }
    else if (event.action == GLFW_RELEASE && window.CursorIsGrabbed())
    {
        window.ReleaseCursor();
    }
}

void RotatableCamera::OnMouseScrollEvent(glm::vec2 scroll)
{
    float speed = m_zoomSensitivity * Time::GetDelta();
    
    m_distance = glm::clamp(m_distance - scroll.y * speed, 3.0f, 10.0f);

    RecalculatePosition();
}

void RotatableCamera::RecalculatePosition()
{
    m_position.x = m_center.x - cos(m_yaw) * m_distance;
    m_position.y = m_center.y - sin(m_pitch) * m_distance;
    m_position.z = m_center.z - sin(m_yaw) * m_distance;

    RecalculateBasisVectors();
}
