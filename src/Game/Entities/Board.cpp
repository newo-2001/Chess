#include "pch.h"
#include "Board.h"
#include <Game/Libraries/Materials.h>
#include <Game/Libraries/Models.h>
#include <Core/Physics/Ray.h>
#include <Core/Rendering/Camera.h>
#include <Game/Game.h>
#include <Core/Debug/Logging.h>
#include <Core/Rendering/Camera.h>
#include <Core/Debug/Rendering.h>

Board::Board(glm::vec3 position) :
    GameObject(Models::Board, glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / 100 / 0.96f * 8)), position), nullptr, Materials::Shiny),
    m_hitBox(glm::vec3(-4, 0, -4), glm::vec2 { 8.0f, 8.0f }, glm::vec3 { 0.0f, 1.0f, 0.0f })
{
    std::shared_ptr<Renderable> mesh = m_hitBox.CreateMesh();
    m_hitBoxObject = std::move(std::make_unique<GameObject>(mesh, glm::mat4(1.0f), nullptr, Materials::White));
}

void Board::Render(Shader& shader) const
{
    Window& window = Game::GetWindow();
    Camera& camera = Game::GetActiveScene().GetCamera();
    
    int highlights = 0;

    if (!window.CursorIsGrabbed())
    {
        Ray ray = camera.CastMouseRay();
        std::optional<glm::vec3> result = ray.Intersect(m_hitBox);

        if (result.has_value())
        {
            glm::vec3 intersection = result.value();
            glm::vec2 square = glm::floor(glm::vec2(intersection.x, intersection.z));

            shader.SetUniform(Uniform<glm::vec2> { "highlights[0].location", square });
            shader.SetUniform(Uniform<glm::vec3> { "highlights[0].color", glm::vec3(1.0f) });
            highlights++;
        }
        
    }

    GameState& state = Game::GetState();
    std::optional<glm::ivec2> selected = state.GetSelectedSquare();
    if (selected.has_value())
    {
        std::string uniform = std::format("highlights[{}]", highlights);
        glm::vec2 selectedSquare = glm::vec2(selected.value() - glm::ivec2(4));

        shader.SetUniform(Uniform<glm::vec2> { uniform + ".location", selectedSquare });
        shader.SetUniform(Uniform<glm::vec3> { uniform + ".color", glm::vec3 { 0.9f, 0.8f, 0.3f }});
        highlights++;
    }
    
    shader.SetUniform(Uniform<int> { "highlightCount", highlights });
    
    GameObject::Render(shader);
    //m_hitBoxObject->Render(shader);
    
    for (size_t x = 0; x < SIZE; x++)
    {
        for (size_t y = 0; y < SIZE; y++)
        {
            const std::unique_ptr<Piece>& piece = PieceAt({ x, y });
            if (!piece) continue;

            piece->Render(shader);
        }
    }
}

void Board::MovePiece(glm::ivec2 from, glm::ivec2 to)
{
    std::unique_ptr<Piece>& piece = PieceAt(from);

    if (!piece)
    {
        throw std::runtime_error("Can't move piece from an empty square");
    }

    piece->SetTransform(glm::translate(m_transform, glm::vec3(to.x, 0.0f, to.y)));
    piece.swap(m_pieces[to.x][to.y]);
}
