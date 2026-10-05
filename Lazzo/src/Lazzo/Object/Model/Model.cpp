#include "lzpch.h"
#include "Model.h"
#include "Lazzo/Log.h"
#include <cctype>
#include <filesystem>
#include <limits>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Lazzo::Object {

    Model::Model(const std::string& path) {
        LoadModel(path);
    }

    void Model::Update(float) {
    }

    void Model::LoadModel(const std::string& path) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path,
            aiProcess_Triangulate |
            aiProcess_FlipUVs |
            aiProcess_GenSmoothNormals);

        if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
            LZ_CORE_ERROR("Model failed to load: {0}", path);
            LZ_CORE_ERROR("Assimp error: {0}", importer.GetErrorString());
            return;
        }

        std::size_t lastSlash = path.find_last_of("/\\");
        m_Directory = (lastSlash == std::string::npos) ? "" : path.substr(0, lastSlash + 1);

        m_Meshes.clear();
        ProcessNode(scene->mRootNode, scene);
    }

    void Model::ProcessNode(aiNode* node, const aiScene* scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            m_Meshes.push_back(ProcessMesh(mesh, scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> vertices;
        vertices.reserve(mesh->mNumVertices);
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            if (mesh->HasNormals()) {
                vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            }
            else {
                vertex.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
            }
            if (mesh->mTextureCoords[0]) {
                vertex.UV = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            }
            else {
                vertex.UV = glm::vec2(0.0f, 0.0f);
            }
            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        Mesh modelMesh(std::move(vertices), std::move(indices));

        if (mesh->mMaterialIndex < scene->mNumMaterials) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            aiColor3D diffuse(1.0f, 1.0f, 1.0f);
            if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS) {
                modelMesh.SetColor(glm::vec3(diffuse.r, diffuse.g, diffuse.b));
            }
            LoadMaterialTextures(material, scene, modelMesh);
        }

        return modelMesh;
    }

    void Model::LoadMaterialTextures(aiMaterial* material, const aiScene* scene, Mesh& mesh) {
        using Lazzo::Graphics::TextureSlot;

        struct SlotQuery {
            TextureSlot slot;
            const char* name;
            std::vector<aiTextureType> types;
        };

        const std::vector<SlotQuery> queries = {
            { TextureSlot::Albedo,   "Albedo",   { aiTextureType_BASE_COLOR, aiTextureType_DIFFUSE } },
            { TextureSlot::Normal,   "Normal",   { aiTextureType_NORMALS, aiTextureType_HEIGHT } },
            { TextureSlot::Specular, "Specular", { aiTextureType_SPECULAR } },
            { TextureSlot::Roughness,"Roughness",{ aiTextureType_DIFFUSE_ROUGHNESS, aiTextureType_GLTF_METALLIC_ROUGHNESS } },
            { TextureSlot::AO,       "AO",       { aiTextureType_AMBIENT_OCCLUSION, aiTextureType_AMBIENT } },
        };

        for (const auto& query : queries) {
            for (aiTextureType type : query.types) {
                if (material->GetTextureCount(type) > 0) {
                    aiString texPath;
                    material->GetTexture(type, 0, &texPath);
                    auto texture = LoadTexture(scene, texPath);
                    if (texture) {
                        mesh.SetTexture(query.slot, texture);
                        LZ_CORE_TRACE("Model '{0}': assigned '{1}' texture", texPath.C_Str(), query.name);
                    }
                    break;
                }
            }
        }
    }

    std::shared_ptr<Lazzo::Graphics::Texture> Model::LoadTexture(const aiScene* scene, const aiString& path) {
        const bool isEmbedded = path.length > 0 && path.C_Str()[0] == '*';

        if (isEmbedded) {
            const std::string key = std::string("embedded:") + path.C_Str();
            auto it = m_TextureCache.find(key);
            if (it != m_TextureCache.end())
                return it->second;

            std::shared_ptr<Lazzo::Graphics::Texture> texture;
            const aiTexture* embedded = scene->GetEmbeddedTexture(path.C_Str());
            if (embedded && embedded->pcData) {
                if (embedded->mHeight == 0) {
                    texture = std::shared_ptr<Lazzo::Graphics::Texture>(
                        Lazzo::Graphics::Texture::CreateFromMemory(embedded->pcData, int(embedded->mWidth), path.C_Str()));
                }
                else {
                    texture = std::shared_ptr<Lazzo::Graphics::Texture>(
                        Lazzo::Graphics::Texture::CreateFromMemory(embedded->pcData, int(embedded->mWidth * embedded->mHeight) * 4, path.C_Str()));
                }
            }
            if (texture && texture->IsValid())
                m_TextureCache[key] = texture;
            return texture;
        }

        for (const auto& candidate : BuildTextureCandidates(path)) {
            FILE* file = fopen(candidate.c_str(), "rb");
            if (!file)
                continue;
            fclose(file);

            auto it = m_TextureCache.find(candidate);
            if (it != m_TextureCache.end())
                return it->second;

            std::shared_ptr<Lazzo::Graphics::Texture> texture = Lazzo::Graphics::Texture::Create(candidate);
            if (texture && texture->IsValid()) {
                m_TextureCache[candidate] = texture;
                LZ_CORE_TRACE("Loaded texture '{0}'", candidate);
                return texture;
            }
        }

        LZ_CORE_WARN("Texture '{0}' not found in any candidate location", path.C_Str());
        return nullptr;
    }

    std::vector<std::string> Model::BuildTextureCandidates(const aiString& path) const {
        std::string filePath = path.C_Str();
        for (char& c : filePath) {
            if (c == '/')
                c = '\\';
        }

        const bool isAbsolute = filePath.size() > 1
            && (filePath[0] == '\\' || filePath[0] == '/'
                || (std::isalpha(static_cast<unsigned char>(filePath[0])) && filePath[1] == ':'));

        const std::size_t lastSep = filePath.find_last_of("\\");
        const std::string filename = (lastSep == std::string::npos) ? filePath : filePath.substr(lastSep + 1);

        std::vector<std::string> candidates;
        auto add = [&candidates](const std::string& candidate) {
            if (candidate.empty())
                return;
            for (const auto& existing : candidates) {
                if (existing == candidate)
                    return;
            }
            candidates.push_back(candidate);
        };

        if (isAbsolute)
            add(filePath);

        if (!isAbsolute && !m_Directory.empty())
            add(m_Directory + filePath);

        if (!m_Directory.empty())
            add(m_Directory + filename);
        add(filename);

        std::filesystem::path dir = m_Directory.empty()
            ? std::filesystem::current_path()
            : std::filesystem::path(m_Directory);
        for (int i = 0; i < 4 && !dir.empty(); i++) {
            std::string dirStr = dir.string();
            if (!dirStr.empty() && dirStr.back() != '\\')
                dirStr += '\\';
            add(dirStr + "Textures\\" + filename);
            add(dirStr + "Texture\\" + filename);
            add(dirStr + filename);

            std::filesystem::path parent = dir.parent_path();
            if (parent == dir)
                break;
            dir = parent;
        }

        return candidates;
    }

    bool Model::GetLocalAABB(glm::vec3& outMin, glm::vec3& outMax) const {
        if (m_Meshes.empty())
            return false;
        glm::vec3 bMin(std::numeric_limits<float>::max());
        glm::vec3 bMax(std::numeric_limits<float>::lowest());
        bool any = false;
        for (const auto& mesh : m_Meshes) {
            for (const auto& vertex : mesh.GetVertices()) {
                bMin = glm::min(bMin, vertex.Position);
                bMax = glm::max(bMax, vertex.Position);
                any = true;
            }
        }
        if (!any)
            return false;
        outMin = bMin;
        outMax = bMax;
        return true;
    }

    bool Model::GetWorldAABB(AABB& outBox) const {
        glm::vec3 localMin, localMax;
        if (!GetLocalAABB(localMin, localMax))
            return false;
        AABB local;
        local.Min = localMin;
        local.Max = localMax;
        outBox = TransformAABB(local, BuildModelMatrix(position, rotation, scale));
        return true;
    }

    void Model::DrawUI(const std::string& label) {        ImGui::PushID(this);
        ImGui::SeparatorText(label.c_str());
        ImGui::DragFloat3("Position", glm::value_ptr(position), 0.01f);
        ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.1f);
        ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.01f);
        ImGui::Text("Meshes: %zu", m_Meshes.size());
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::PopID();
    }

    void Model::Draw(const Lazzo::Object::Camera::Camera& camera, const std::vector<Lazzo::Object::Lights::Light*>& lights) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, scale);

        for (auto& mesh : m_Meshes) {
            mesh.Draw(model, camera, lights);
        }
    }
}