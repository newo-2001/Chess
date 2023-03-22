#pragma once
#include <Core/Rendering/GameObject.h>
#include "AnimatedObject.h"

class Animator
{
public:
    void Animate(float dt);
private:
    std::vector<AnimatedObject> m_animations;
};

