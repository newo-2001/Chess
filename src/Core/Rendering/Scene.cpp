#include "pch.h"
#include "Scene.h"

void Scene::AddObject(std::shared_ptr<GameObject>& object)
{
    m_objects.push_back(object);
}

void Scene::AddLight(std::string name, std::shared_ptr<LightSource>& light)
{
    m_lights.insert({ name, light });
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
    for (const std::shared_ptr<GameObject>& object : m_objects)
    {
        object->Render(shader);
    }
}
