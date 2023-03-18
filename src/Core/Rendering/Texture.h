#pragma once

#include "pch.h"

class Texture
{
public:
    Texture(const std::string& filePath, bool hasAlpha = false);
    ~Texture();

    void Use(unsigned int textureUnit);

    glm::ivec2 GetDimensions() const { return m_dimensions; }
    int GetBitDepth() const { return m_bitDepth; }
private:
    int m_bitDepth;
    glm::ivec2 m_dimensions;
    GLuint m_texture;
};

