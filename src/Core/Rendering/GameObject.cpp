#include "pch.h"
#include "GameObject.h"

#include <Game/Libraries/Textures.h>

GameObject::GameObject(std::shared_ptr<Renderable>& renderable, glm::mat4 transform,
                       std::shared_ptr<Texture> texture, std::shared_ptr<Material> material) :
    m_renderable(renderable),
    m_transform(transform),
    m_texture(texture),
    m_material(material)
{ }

void GameObject::Render(Shader& shader) const
{
    shader.SetUniform(Uniform<glm::mat4> { "model", m_transform });
    
    if (m_texture)
    {
        m_texture->Use(0);
    }
    {
        Textures::Plain->Use(0);
    }

    if (m_material)
    {
        m_material->Use(shader);
    }

    m_renderable->Render();
}