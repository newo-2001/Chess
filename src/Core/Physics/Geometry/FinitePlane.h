#pragma once
#include "Plane.h"
#include <Core/Rendering/Mesh.h>

class FinitePlane : public Plane
{
public:
    FinitePlane(glm::vec3 position, glm::vec2 dimensions, glm::vec3 normal, float angle = 0.0f);

    glm::vec2 GetDimensions() const { return m_dimensions; }
    float GetRotation() const { return m_rotation; }

    std::unique_ptr<Mesh> CreateMesh() const;
private:
    glm::vec2 m_dimensions;
    float m_rotation;
};

