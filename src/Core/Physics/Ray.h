#pragma once
#include "pch.h"
#include "Geometry/Plane.h"
#include "Geometry/FinitePlane.h"

class Ray
{
public:
    Ray(glm::vec3 start, glm::vec3 direction, float length = 100.0f);

    glm::vec3 GetDirection() const { return m_direction; }
    glm::vec3 GetStart() const { return m_start; }

    glm::vec3 GetEnd() const { return m_start + m_direction * m_length; }

    std::optional<glm::vec3> Intersect(Plane plane) const;
    std::optional<glm::vec3> Intersect(FinitePlane plane) const;
private:
    glm::vec3 m_start, m_direction;
    float m_length;
};

