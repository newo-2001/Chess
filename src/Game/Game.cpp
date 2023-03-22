#include "pch.h"
#include "Game.h"
#include <Core/Rendering/Scene.h>
#include <Core/Rendering/Lighting/DirectionalLight.h>
#include <Core/Rendering/Model.h>
#include <Core/Time.h>
#include <Core/Input/MovableCamera.h>
#include <Core/Physics/Geometry/Cube.h>
#include "Entities/Board.h"
#include <Core/Input/RotatableCamera.h>
#include "Libraries/Models.h"
#include "Libraries/Textures.h"
#include "Libraries/Materials.h"
#include <Core/Debug/Rendering.h>
#include "GameState.h"

std::shared_ptr<GameState> state;
Window window({ 1366, 768 }, "Chess");
Scene scene;

Window& Game::GetWindow() { return window; }
Scene& Game::GetActiveScene() { return scene; }
GameState& Game::GetState() { return *state; }

void Update()
{
    Time::Update();
    float delta = Time::GetDelta();

    scene.GetCamera().Update(delta);
}

void Render()
{
    window.Update();
    scene.Render();
}

void Initialize()
{
    Textures::Load();
    Models::Load();
    Debug::Initialize();

    std::shared_ptr<Camera> camera = std::make_shared<RotatableCamera>(glm::vec3(0.0f, 0.0f, 0.0f), 5.0f, 90.0f);
    scene.UseCamera(camera);

    std::shared_ptr<Shader> shader = std::make_shared<Shader>("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
    scene.UseShader(shader);

    glm::vec3 white = glm::vec3(1.0f);

    glm::vec3 lightDirection = glm::vec3 { 5.0, -2.0f, 1.0f };
    std::shared_ptr<LightSource> directionalLight = std::make_shared<DirectionalLight>(
        white, glm::vec2 { 0.3f, 1.0f },
        lightDirection
    );

    scene.AddLight("directionalLight", directionalLight);
    
    std::shared_ptr<Texture> plain = std::make_shared<Texture>("resources/textures/plain.png", true);
    
    std::shared_ptr<Board> board = std::make_shared<Board>();
    std::shared_ptr<GameObject> boardObject = board;
    scene.AddObject("board", boardObject);

    state = std::make_unique<GameState>(board);
    
    /*glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    std::shared_ptr<Renderable> cubeMesh = std::make_shared<Cube>();
    std::shared_ptr<GameObject> origin = std::make_shared<GameObject>(cubeMesh, model, plain, Materials::Dull);
    scene.AddObject("cube", origin);*/
}

void Game::Run()
{
    Initialize();

    while (!window.IsClosed())
    {
        Update();
        Render();
    }
}
