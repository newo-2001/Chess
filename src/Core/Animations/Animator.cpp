#include "pch.h"
#include "Animator.h"

void Animator::Animate(float dt)
{
    auto it = m_animations.begin();
    while (it != m_animations.end())
    {
        AnimatedObject& object = *it;
        
        if (object.Animate(dt))
        {
            m_animations.erase(it);
        }
        else
        {
            it++;
        }
    }
}
