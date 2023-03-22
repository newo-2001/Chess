#include "pch.h"
#include "Rendering.h"
#include <Core/Rendering/Shader.h>
#include <Core/Rendering/Camera.h>
#include <Game/Game.h>

GLuint VBO;
GLuint VAO;
std::unique_ptr<Shader> shader;

void Debug::Initialize()
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    shader = std::make_unique<Shader>("resources/shaders/debug.vertex.glsl", "resources/shaders/debug.fragment.glsl");

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (void*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Debug::Line(glm::vec3 from, glm::vec3 to, glm::vec3 color)
{
    Camera& camera = Game::GetActiveScene().GetCamera();
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjectionMatrix();

    GLfloat vertices[] = {
        from.x, from.y, from.z,
        to.x, to.y, to.z
    };
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    shader->Bind();
    shader->SetUniform(Uniform<glm::mat4> { "projection", projection });
    shader->SetUniform(Uniform<glm::mat4> { "view", view });
    shader->SetUniform(Uniform<glm::vec3> { "color", color });

    glDrawArrays(GL_LINES, 0, 2);

    shader->Unbind();
    
    glBindVertexArray(0);
}
