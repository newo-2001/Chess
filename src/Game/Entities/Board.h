#pragma once

#include "pch.h"
#include <Core/Rendering/Model.h>
#include <Core/Rendering/GameObject.h>

class Board : public GameObject
{
public:
    Board(glm::vec3 position = glm::vec3());

    static void Load();
private:
    inline static std::shared_ptr<Renderable> s_model = nullptr;
};
