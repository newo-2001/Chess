#pragma once

#include "pch.h"
#include "Shader.h"
#include "Camera.h"
#include "GameObject.h"
#include "Lighting/LightSource.h"

class Scene
{
public:
    void Render() const;

    void UseShader(std::shared_ptr<Shader>& shader) { m_shader = shader; }
    void UseCamera(std::shared_ptr<Camera>& camera) { m_camera = camera; }

    Camera& GetCamera() const { return *m_camera; }

    void AddObject(std::shared_ptr<GameObject>& object);
    void AddLight(std::string name, std::shared_ptr<LightSource>& light);

    Shader& GetActiveShader() const { return *m_shader; }
private:
    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<Camera> m_camera;

    std::vector<std::shared_ptr<GameObject>> m_objects;
    std::unordered_map<std::string, std::shared_ptr<LightSource>> m_lights;

    void RenderScene(Shader& shader) const;
};

