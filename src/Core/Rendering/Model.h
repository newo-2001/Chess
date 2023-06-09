#pragma once

#include "pch.h"
#include "Renderable.h"

#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Mesh.h"
#include "Texture.h"

class Model : public Renderable
{
public:
    Model(const std::string& filePath);

    void Render() const;
private:
    std::vector<std::unique_ptr<Mesh>> m_meshes;
    std::vector<std::shared_ptr<Texture>> m_textures;
    std::vector<size_t> m_meshTextureIndices;

    void LoadNode(aiNode* node, const aiScene* scene);
    void LoadMesh(aiMesh* mesh, const aiScene* scene);
    void LoadMaterials(const aiScene* scene);
};

