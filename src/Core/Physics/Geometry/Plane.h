#pragma once
#include "pch.h"

class Plane
{
public:
    Plane(glm::vec3 point, glm::vec3 normal);

    glm::vec3 GetNormal() const { return m_normal; }
    glm::vec3 GetPoint() const { return m_point; }

    glm::mat3x2 GetBasis() const;

    virtual glm::vec2 ProjectPoint(glm::vec3 point) const;
protected:
    glm::vec3 m_point, m_normal;
};

