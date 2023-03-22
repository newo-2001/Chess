#include "pch.h"
#include "Camera.h"
#include <Game/Game.h>
#include <Core/Debug/Logging.h>

Camera::Camera(glm::vec3 position, float yaw, float pitch,
               float fov, float near, float far) :
    m_position(position),
    m_yaw(glm::radians(yaw)),
    m_pitch(glm::radians(pitch)),
    m_near(near),
    m_far(far)
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
    m_fov = glm::radians(fov);
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

Ray Camera::CastMouseRay()
{
    Window& window = Game::GetWindow();

    glm::vec2 cursorPos = window.GetInputHandler().GetMousePosition();
    glm::vec2 windowSize = window.GetViewportDimensions();
    cursorPos.y = windowSize.y - cursorPos.y;

    glm::vec4 viewport(0.0f, 0.0f, windowSize.x, windowSize.y);
    glm::vec3 near = glm::unProject(glm::vec3(cursorPos, m_near), GetViewMatrix(), GetProjectionMatrix(), viewport);
    glm::vec3 far = glm::unProject(glm::vec3(cursorPos, m_far), GetViewMatrix(), GetProjectionMatrix(), viewport);

    return Ray(GetPosition(), glm::normalize(far - near));
}
