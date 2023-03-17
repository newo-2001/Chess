#pragma once

#include "pch.h"

struct KeyEvent
{
    int key;
    int action;
};

struct MouseButtonEvent
{
    int button;
    int action;
};

struct MouseMoveEvent
{
    glm::vec2 current;
    glm::vec2 delta;
};
