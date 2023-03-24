#pragma once

#include "pch.h"

#include <Core/Rendering/Window.h>
#include <Core/Rendering/Scene.h>
#include <Game/GameState.h>
#include "Engine/Stockfish.h"

namespace Game
{
    Window& GetWindow();
    Scene& GetActiveScene();
    GameState& GetState();
    Stockfish& GetStockfish();

    void Run();
}
