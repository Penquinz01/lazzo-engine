#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "Lazzo/Core.h"
#include "Lazzo/Object/GameObject.h"
#include "Lazzo/Object/Model/Mesh.h"
#include "Lazzo/Object/Picking.h"
#include "Lazzo/Window/GraphicsAPI/Texture.h"

struct aiMaterial;
struct aiNode;
struct aiScene;
struct aiMesh;
struct aiString;

namespace Lazzo::Object {

    class LAZZO_API Model : public GameObject {
    public:
        Model() = default;
        explicit Model(const std::string& path);
        ~Model() override = default;

        Model(const Model&) = delete;
        Model& operator=(const Model&) = delete;

        void Update(float deltaTime) override;
        void LoadModel(const std::string& path);

        void Draw(const Lazzo::Object::Camera::Camera& camera, const std::vector<Lazzo::Object::Lights::Light*>& lights);
        void DrawUI(const std::string& label = "Model");

        const std::vector<Mesh>& GetMeshes() const { return m_Meshes; }

        // Local-space bounds over all mesh vertices (false when no meshes loaded).
        bool GetLocalAABB(glm::vec3& outMin, glm::vec3& outMax) const;
        // World-space bounds from the GameObject transform (false when no meshes loaded).
        bool GetWorldAABB(AABB& outBox) const;

    private:
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        void LoadMaterialTextures(aiMaterial* material, const aiScene* scene, Mesh& mesh);
        std::shared_ptr<Lazzo::Graphics::Texture> LoadTexture(const aiScene* scene, const aiString& path);
        std::vector<std::string> BuildTextureCandidates(const aiString& path) const;

        std::vector<Mesh> m_Meshes;
        std::string m_Directory;
        std::unordered_map<std::string, std::shared_ptr<Lazzo::Graphics::Texture>> m_TextureCache;
    };
}