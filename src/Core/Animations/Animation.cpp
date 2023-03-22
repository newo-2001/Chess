#include "pch.h"
#include "Animation.h"

Animation::Animation(std::vector<KeyFrame> frames)
    : m_keyFrames(frames)
{ }

float Animation::GetDuration() const
{
    return GetEndTime(m_keyFrames.back());
}

float Animation::GetEndTime(const KeyFrame& frame) const
{
    float total = 0;

    for (const KeyFrame& current : m_keyFrames)
    {
        total += current.Duration;
        if (&frame == &current)
        {
            return total;
        }
    }

    throw std::runtime_error("Frame not found in animation");
}

const KeyFrame& Animation::GetKeyFrameAt(float time) const
{
    float end = 0;
    
    for (const KeyFrame& frame : m_keyFrames)
    {
        end += frame.Duration;
        if (time < end) return frame;
    }

    throw std::invalid_argument(std::format("Time {}, was greater than animation duration of {}", time, GetDuration()));
}

glm::vec3 Animation::GetTransformAt(float time) const
{
    float end = 0;
    glm::vec3 pos = glm::vec3();

    for (const KeyFrame& frame : m_keyFrames)
    {
        float start = end;
        end += frame.Duration;
        
        if (time < end)
        {
            float frameProgress = time - start / (end - start);
            pos += frame.Path * frameProgress;
            return pos;
        }

        pos += frame.Path;
    }

    return pos;
}
