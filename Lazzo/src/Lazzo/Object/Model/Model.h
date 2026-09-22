#pragma once
#include <string>
#include <vector>
#include "Lazzo/Core.h"
#include "Lazzo/Object/GameObject.h"
#include "Lazzo/Object/Model/Mesh.h"

struct aiNode;
struct aiScene;
struct aiMesh;

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

        const std::vector<Mesh>& GetMeshes() const { return m_Meshes; }

    private:
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

        std::vector<Mesh> m_Meshes;
        std::string m_Directory;
    };
}