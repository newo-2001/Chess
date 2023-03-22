#include "pch.h"
#include "Textures.h"

std::shared_ptr<Texture> LoadFile(const std::string& path, bool hasAlpha = false)
{
    return std::make_shared<Texture>("resources/textures/" + path, hasAlpha);
}

void Textures::Load()
{
    Plain = LoadFile("plain.png", true);
}
