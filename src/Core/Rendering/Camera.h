#pragma once
#include "pch.h"
#include <Core/Physics/Ray.h>

class Camera
{
public:
    const glm::vec3 WORLD_UP = glm::vec3 { 0.0f, 1.0f, 0.0f };

    Camera(glm::vec3 position = glm::vec3(), float yaw = 0.0f, float pitch = 0.0f,
           float fov = 60.0f, float near = 0.1f, float far = 100.0f);

    glm::vec3 GetPosition() const { return m_position; }
    glm::vec3 GetOrientation() const { return m_front; }

    float GetYaw() const { return m_yaw; }
    float GetPitch() const { return m_pitch; }

    float GetNear() const { return m_near; }
    float GetFar() const { return m_far; }

    void SetFov(float fov);
    float GetFov() const { return m_fov; }

    Ray CastMouseRay();

    void MoveTo(glm::vec3 position) { m_position = position; }

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const { return m_projection; }

    virtual void Update(float delta) {};
protected:
    glm::vec3 m_position, m_front, m_up, m_right;
    float m_yaw, m_pitch;
    float m_near, m_far;
    float m_fov;

    glm::mat4 m_projection;

    void RecalculateBasisVectors();
};

