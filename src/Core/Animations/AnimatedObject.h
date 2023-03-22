#pragma once

#include "pch.h"
#include <Core/Rendering/GameObject.h>
#include "Animation.h"

class AnimatedObject
{
public:
    AnimatedObject(std::weak_ptr<GameObject> object, Animation animation);
    
    float GetProgress() const { return m_progress; }
    bool IsFinished() const { return m_progress >= m_animation.GetDuration(); }
    
    bool Animate(float dt);
private:
    std::weak_ptr<GameObject> m_object;
    Animation m_animation;
    float m_progress = 0;
    glm::mat4 m_anchor;
};

