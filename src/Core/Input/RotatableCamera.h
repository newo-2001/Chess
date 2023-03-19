#pragma once

#include "pch.h"
#include <Core/Rendering/Camera.h>
#include <Core/Events/Events.h>

class RotatableCamera : public Camera
{
public:
    RotatableCamera(glm::vec3 center, float distance = 10.0f, float yaw = 0.0f, float pitch = -20.0f, float fov = 90.0f);
    ~RotatableCamera();
private:
    glm::vec3 m_center;
    float m_distance;
    float m_mouseSensitivity = 0.01f;
    float m_zoomSensitivity = 3.0f;

    long m_mouseMoveEventSubscription;
    long m_mouseButtonEventSubscription;
    long m_mouseScrollEventSubscription;

    void RecalculatePosition();

    void OnMouseButtonEvent(MouseButtonEvent event);
    void OnMouseMoveEvent(glm::vec2 delta);
    void OnMouseScrollEvent(glm::vec2 scroll);
};
