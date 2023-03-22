#include "pch.h"
#include "Plane.h"

Plane::Plane(glm::vec3 point, glm::vec3 normal) :
    m_point(point),
    m_normal(glm::normalize(normal))
{ }

glm::mat3x2 Plane::FromLocal() const
{
    glm::vec3 indep = glm::all(glm::equal(m_normal, { 1.0f, 0.0f, 0.0f }))
        ? glm::vec3 { 0.0f, 0.0f, 1.0f }
        : glm::vec3 { 1.0f, 0.0f, 0.0f };

    glm::vec3 basisX = glm::cross(indep, m_normal);
    glm::vec3 basisY = glm::cross(m_normal, basisX);
    
    return glm::transpose(glm::mat2x3(basisX, basisY));
}
