#include "pch.h"
#include <Game/Game.h>
#include "MovableCamera.h"
#include "InputHandler.h"
#include <numbers>

MovableCamera::MovableCamera(glm::vec3 position, float yaw, float pitch,
                             float fov, float near, float far) :
    Camera(position, yaw, pitch, fov, near, far)
{
    Window& window = Game::GetWindow();
    InputHandler& inputHandler = window.GetInputHandler();

    if (!window.CursorIsGrabbed())
    {
        window.GrabCursor();
    }

    m_mouseMoveEventSubscription = inputHandler.OnMouseMoveEvent.Subscribe([this] (MouseMoveEvent event) -> void
    {
        this->OnMouseMoved(event);
    });

    m_mouseButtonEventSubscription = inputHandler.OnMouseButtonEvent.Subscribe([this] (MouseButtonEvent event) -> void
    {
        this->OnMouseButtonPressed(event);
    });
}

MovableCamera::~MovableCamera()
{
    InputHandler& inputHandler = Game::GetWindow().GetInputHandler();
    inputHandler.OnMouseMoveEvent.Unsubscribe(m_mouseMoveEventSubscription);
}

void MovableCamera::Update(float delta)
{
    InputHandler& inputHandler = Game::GetWindow().GetInputHandler();
    float speed = m_movementSpeed * delta;
    
    if (inputHandler.IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
    {
        speed *= 2;
    }

    glm::vec3 front = glm::normalize(glm::vec3 { m_front.x, 0.0f, m_front.z }) * speed;
    glm::vec3 right = glm::normalize(glm::vec3 { m_right.x, 0.0f, m_right.z }) * speed;

    if (inputHandler.IsKeyPressed(GLFW_KEY_W))
    {
        m_position += front;
    }
    
    if (inputHandler.IsKeyPressed(GLFW_KEY_S))
    {
        m_position -= front;
    }

    if (inputHandler.IsKeyPressed(GLFW_KEY_A))
    {
        m_position -= right;
    }

    if (inputHandler.IsKeyPressed(GLFW_KEY_D))
    {
        m_position += right;
    }

    if (inputHandler.IsKeyPressed(GLFW_KEY_SPACE))
    {
        m_position += WORLD_UP * speed;
    }

    if (inputHandler.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        m_position -= WORLD_UP * speed;
    }
}

void MovableCamera::OnMouseMoved(MouseMoveEvent event)
{
    constexpr float MAX_ANGLE = (float) (std::numbers::pi / 2) - 0.05f;
    constexpr float MIN_ANGLE = -MAX_ANGLE;
    
    m_yaw = fmod(m_yaw + event.delta.x * m_mouseSensitivity, (float) std::numbers::pi * 2);
    m_pitch = glm::clamp(m_pitch - event.delta.y * m_mouseSensitivity, MIN_ANGLE, MAX_ANGLE);

    Camera::RecalculateBasisVectors();
}

void MovableCamera::OnMouseButtonPressed(MouseButtonEvent event)
{
    if (event.action != GLFW_PRESS) return;

    Window& window = Game::GetWindow();

    if (event.button == GLFW_MOUSE_BUTTON_RIGHT && window.CursorIsGrabbed())
    {
        window.ReleaseCursor();
    }
    else if (event.button == GLFW_MOUSE_BUTTON_LEFT && !window.CursorIsGrabbed())
    {
        window.GrabCursor();
    }
}