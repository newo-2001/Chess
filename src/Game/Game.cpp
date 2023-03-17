#include "pch.h"
#include "Game.h"

Window window({ 1366, 768 }, "Chess");

Window& Game::GetWindow() { return window; }

void Update()
{
    
}

void Render()
{
    window.Update();
}

void Game::Run()
{
    while (!window.IsClosed())
    {
        Update();
        Render();
    }
}
