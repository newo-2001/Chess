#pragma once
#include "KeyFrame.h"

class Animation
{
public:
    Animation(std::vector<KeyFrame> frames);
    
    float GetDuration() const;
    glm::vec3 GetTransformAt(float time) const;

    float GetEndTime(const KeyFrame& frame) const;

    const KeyFrame& GetKeyFrameAt(float time) const;
private:
    std::vector<KeyFrame> m_keyFrames;
};

