#include "pch.h"
#include "FinitePlane.h"

FinitePlane::FinitePlane(glm::vec3 position, glm::vec2 dimensions, glm::vec3 normal, float rotation) :
    Plane(position, normal),
    m_dimensions(dimensions),
    m_rotation(rotation)
{ }

std::unique_ptr<Mesh> FinitePlane::CreateMesh() const
{
    glm::mat3x2 basis = GetBasis();

    const glm::vec3& normal = m_normal;

    const glm::vec2 corners[] = {
        { 0.0f, 0.0f }, { m_dimensions.x, 0.0f },
        { 0.0f, m_dimensions.y }, { m_dimensions.x, m_dimensions.y }
    };

    GLfloat vertices[] = {
        0.0f, 0.0f, 0.0f,   0.0f, 0.0f,     normal.x, normal.y, normal.z,
        0.0f, 0.0f, 0.0f,   1.0f, 0.0f,     normal.x, normal.y, normal.z,
        0.0f, 0.0f, 0.0f,   0.0f, 1.0f,     normal.x, normal.y, normal.z,
        0.0f, 0.0f, 0.0f,   1.0f, 1.0f,     normal.x, normal.y, normal.z
    };

    unsigned int indices[] = {
        2, 0, 1,
        2, 3, 1
    };
    
    const size_t STRIDE = 8;
    for (int i = 0; i < 4; i++)
    {
        glm::vec3& vec = *((glm::vec3*) &vertices[i * STRIDE]);
        vec = corners[i] * basis + m_point;
    }

    return std::make_unique<Mesh>(vertices, 4, indices, 6);
}

glm::vec2 FinitePlane::ProjectPoint(glm::vec3 point) const
{
    return Plane::ProjectPoint(point - m_point);
}
