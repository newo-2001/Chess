#include "pch.h"
#include "AnimatedObject.h"

AnimatedObject::AnimatedObject(std::weak_ptr<GameObject> object, Animation animation) :
    m_animation(animation),
    m_object(object),
    m_anchor(object.lock()->GetTransform())
{ }

bool AnimatedObject::Animate(float dt)
{
    if (m_object.expired()) return true;
    std::shared_ptr<GameObject> object = m_object.lock();

    float prev = m_progress;
    m_progress += dt;
    
    const KeyFrame& lastFrame = m_animation.GetKeyFrameAt(prev);
    const KeyFrame& currentFrame = m_animation.GetKeyFrameAt(dt);

    if (&lastFrame != &currentFrame)
    {
        m_anchor = glm::translate(m_anchor, lastFrame.Path);
        dt = m_progress - m_animation.GetEndTime(lastFrame);
    }

    if (!IsFinished())
    {
        glm::vec3 delta = dt * currentFrame.Path;
        object->SetTransform(glm::translate(object->GetTransform(), delta));
        return false;
    }
    
    return true;
}
