#include "pch.h"
#include "Materials.h"

std::shared_ptr<Material> Materials::Dull = std::make_shared<Material>(0.3f, 0.05f);
std::shared_ptr<Material> Materials::Shiny = std::make_shared<Material>(0.3f, 1.0f);