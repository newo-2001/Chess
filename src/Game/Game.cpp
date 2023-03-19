#include "pch.h"
#include "Game.h"
#include <Core/Rendering/Scene.h>
#include <Core/Rendering/Lighting/DirectionalLight.h>
#include <Core/Rendering/Model.h>
#include <Core/Time.h>
#include <Core/Input/MovableCamera.h>
#include <Core/Rendering/Primitives/Cube.h>
#include "Entities/Board.h"

Window window({ 1366, 768 }, "Chess");
Scene scene;

Window& Game::GetWindow() { return window; }

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
    std::shared_ptr<Camera> camera = std::make_shared<MovableCamera>(glm::vec3(0.0f, 0.0f, -5.0f), 90.0f, 0.0f);
    scene.UseCamera(camera);

    std::shared_ptr<Shader> shader = std::make_shared<Shader>("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
    scene.UseShader(shader);

    glm::vec3 white = glm::vec3(1.0f);

    glm::vec3 lightPosition = glm::vec3 { 5.0, -2.0f, 1.0f };
    std::shared_ptr<LightSource> directionalLight = std::make_shared<DirectionalLight>(
        white, glm::vec2 { 0.3f, 1.0f },
        lightPosition
    );

    scene.AddLight("directionalLight", directionalLight);
    
    std::shared_ptr<Material> dull = std::make_shared<Material>(0.3f, 4.0f);
    std::shared_ptr<Material> shiny = std::make_shared<Material>(1.0f, 256.0f);

    std::shared_ptr<Texture> plain = std::make_shared<Texture>("resources/textures/plain.png", true);
    
    Board::Load();
    std::shared_ptr<GameObject> board = std::make_shared<Board>();
    scene.AddObject(board);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPosition);
    std::shared_ptr<Renderable> cubeMesh = std::make_shared<Cube>();
    std::shared_ptr<GameObject> lightSource = std::make_shared<GameObject>(cubeMesh, model, plain, shiny);
    scene.AddObject(lightSource);
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
