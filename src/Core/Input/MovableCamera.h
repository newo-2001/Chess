#pragma once

#include "pch.h"
#include <Core/Events/Events.h>
#include <Core/Rendering/Camera.h>

class MovableCamera : public Camera
{
public:
    MovableCamera(glm::vec3 position = glm::vec3(), float yaw = 0.0f, float pitch = 0.0f, float fov = 90.0f);
    ~MovableCamera();

    void SetMovementSpeed(float speed) { m_movementSpeed = speed; }
    float GetMovementSpeed() { return m_movementSpeed; }

    void Update(float delta);
    void OnMouseMoved(MouseMoveEvent event);
    void OnMouseButtonPressed(MouseButtonEvent event);
private:
    float m_movementSpeed = 0.2f;
    float m_mouseSensitivity = 0.002f;
    
    long m_mouseMoveEventSubscription, m_mouseButtonEventSubscription;
};