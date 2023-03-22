#pragma once

#include "pch.h"

#include <Core/Rendering/Window.h>
#include <Core/Rendering/Scene.h>

namespace Game
{
    Window& GetWindow();
    Scene& GetActiveScene();

    void Run();
}
