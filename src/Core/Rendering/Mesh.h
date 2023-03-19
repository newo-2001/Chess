#pragma once

#include "pch.h"
#include "Shader.h"
#include "Renderable.h"

class Mesh : public Renderable
{
public:
    Mesh(const GLfloat* const vertices, size_t vertexCount, const unsigned int* const indices, size_t indexCount);
    ~Mesh();

    void Render() const;
private:
    GLuint m_VAO, m_VBO, m_IBO;
    GLsizei m_indices;
};

