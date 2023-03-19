#pragma once

#include "pch.h"

namespace Time
{
    void Update();

    unsigned int GetFps();
    float GetDelta();

    extern const unsigned int TPS;
}
