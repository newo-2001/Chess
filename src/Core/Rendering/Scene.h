#pragma once

#include "pch.h"
#include "Shader.h"
#include "Renderable.h"
#include "Camera.h"

class Scene
{
public:
    void Render() const;

    void UseShader(std::shared_ptr<Shader>& shader) { m_shader = shader; }
    void UseCamera(std::shared_ptr<Camera>& camera) { m_camera = camera; }

    void AddObject(std::shared_ptr<Renderable>& renderable);

    Shader& GetActiveShader() const { return *m_shader; }
private:
    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<Camera> m_camera;
    std::vector<std::shared_ptr<Renderable>> m_objects;

    void RenderScene(Shader& shader) const;
};

