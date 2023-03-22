#include "pch.h"
#include "Materials.h"

std::shared_ptr<Material> Materials::Dull = std::make_shared<Material>(0.3f, 0.05f);
std::shared_ptr<Material> Materials::Shiny = std::make_shared<Material>(0.3f, 1.0f);
std::shared_ptr<Material> Materials::Black = std::make_shared<Material>(0.3f, 1.0f, glm::vec3 {0.12f, 0.12f, 0.12f });
std::shared_ptr<Material> Materials::White = std::make_shared<Material>(0.3f, 1.0f);