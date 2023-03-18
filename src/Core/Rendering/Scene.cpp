#include "pch.h"
#include "Scene.h"

void Scene::AddObject(std::shared_ptr<Renderable>& object)
{
    m_objects.push_back(object);
}

void Scene::Render() const
{
    if (!m_shader || !m_camera) return;
    
    m_shader->SetUniform<glm::mat4>({ "projection", m_camera->GetProjectionMatrix() });
    m_shader->SetUniform<glm::mat4>({ "view", m_camera->GetViewMatrix() });

    RenderScene(*m_shader);
}

void Scene::RenderScene(Shader& shader) const
{
    shader.Bind();

    for (const std::shared_ptr<Renderable>& object : m_objects)
    {
        object->Render(shader);
    }

    shader.Unbind();
}
