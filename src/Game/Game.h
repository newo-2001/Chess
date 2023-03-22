#pragma once

#include "pch.h"

#include <Core/Rendering/Window.h>
#include <Core/Rendering/Scene.h>
#include <Game/GameState.h>

namespace Game
{
    Window& GetWindow();
    Scene& GetActiveScene();
    GameState& GetState();

    void Run();
}
