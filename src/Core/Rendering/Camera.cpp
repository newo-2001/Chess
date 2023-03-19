#include "pch.h"
#include "Camera.h"
#include <Game/Game.h>

Camera::Camera(glm::vec3 position, float yaw, float pitch, float fov) :
    m_position(position),
    m_yaw(glm::radians(yaw)),
    m_pitch(glm::radians(pitch))
{
    SetFov(fov);
    RecalculateBasisVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::SetFov(float fov)
{
    Window& window = Game::GetWindow();
    glm::ivec2 dimensions = window.GetViewportDimensions();
    float aspect = (float) dimensions.x / dimensions.y;

    m_projection = glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
}

void Camera::RecalculateBasisVectors()
{
    m_front.x = cos(m_yaw) * cos(m_pitch);
    m_front.y = sin(m_pitch);
    m_front.z = sin(m_yaw) * cos(m_pitch);
    m_front = glm::normalize(m_front);

    m_right = glm::normalize(glm::cross(m_front, WORLD_UP));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
