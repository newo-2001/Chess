#include "pch.h"
#include "Time.h"


double lastFrameTime = glfwGetTime();
float delta = 1.0f;

namespace Time
{
    const unsigned int TPS = 30;
    
    void Update()
    {
        double time = glfwGetTime();

        double diff = time - lastFrameTime;
        lastFrameTime = time;

        delta = (float) (TPS / (1.0f / diff));
    }

    unsigned int GetFps()
    {
        return (unsigned int) (TPS / delta);
    }

    float GetDelta()
    {
        return delta;
    }
}