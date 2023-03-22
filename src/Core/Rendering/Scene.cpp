#include "pch.h"
#include "Scene.h"

void Scene::AddObject(std::string name, std::shared_ptr<GameObject>& object)
{
    m_objects.insert({ name, object });
}

void Scene::AddLight(std::string name, std::shared_ptr<LightSource>& light)
{
    m_lights.insert({ name, light });
}

std::optional<std::shared_ptr<GameObject>> Scene::GetObject(const std::string& name) const
{
    auto it = m_objects.find(name);
    return it != m_objects.end() ? std::make_optional(it->second) : std::nullopt;
}

void Scene::Render() const
{
    if (!m_shader || !m_camera) return;

    m_shader->Bind();
    
    m_shader->SetUniform<glm::mat4>({ "projection", m_camera->GetProjectionMatrix() });
    m_shader->SetUniform<glm::mat4>({ "view", m_camera->GetViewMatrix() });

    m_shader->SetUniform<glm::vec3>({ "cameraPos", m_camera->GetPosition() });

    for (const auto& light : m_lights)
    {
        light.second->Use(light.first, *m_shader);
    }

    RenderScene(*m_shader);
    
    m_shader->Unbind();
}

void Scene::RenderScene(Shader& shader) const
{
    for (const auto object : m_objects)
    {
        object.second->Render(shader);
    }
}
