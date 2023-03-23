#include "pch.h"
#include "Ray.h"

Ray::Ray(glm::vec3 start, glm::vec3 direction, float length) :
    m_start(start),
    m_direction(glm::normalize(direction)),
    m_length(length)
{ }

std::optional<glm::vec3> Ray::Intersect(Plane plane) const
{
    glm::vec3 normal = plane.GetNormal();
    glm::vec3 delta = m_start - GetEnd();
    glm::vec3 rayToPlane = plane.GetPoint() - m_start;

    float scale = glm::dot(rayToPlane, normal) / glm::dot(delta, normal);

    if (scale < 0 || scale > 1)
    {
        return std::nullopt;
    }
    
    return m_start + scale * delta;
}

std::optional<glm::vec3> Ray::Intersect(FinitePlane plane) const
{
    std::optional<glm::vec3> intersection = Intersect((Plane) plane);

    if (!intersection.has_value()) return std::nullopt;
    
    glm::vec2 hit = plane.ProjectPoint(intersection.value());
    glm::vec2 dimensions = plane.GetDimensions();

    return hit.x >= 0 && hit.y >= 0 && hit.x <= dimensions.x && hit.y <= dimensions.y
        ? intersection : std::nullopt;
   
    /*return (point.x >= bottomLeft.x && point.y >= bottomLeft.y && point.z >= bottomLeft.z &&
            point.x <= topRight.x && point.y <= topRight.y && point.z <= topRight.z)
        ? intersection : std::nullopt;*/
}
