#pragma once

#include "pch.h"

namespace Debug
{
    void Initialize();
    void Line(glm::vec3 from, glm::vec3 to, glm::vec3 color = glm::vec3 { 0.0f, 1.0f, 0.0f });
}