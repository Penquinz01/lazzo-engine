#pragma once
#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Lazzo/Core.h"
#include "Lazzo/Object/Camera/Camera.h"
#include "Lazzo/Object/Lights/Light.h"
#include "Lazzo/Window/GraphicsAPI/IndexBuffer.h"
#include "Lazzo/Window/GraphicsAPI/Material.h"
#include "Lazzo/Window/GraphicsAPI/Renderer.h"
#include "Lazzo/Window/GraphicsAPI/VertexArray.h"
#include "Lazzo/Window/GraphicsAPI/VertexBuffer.h"

namespace Lazzo::Object {

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 UV;
    };

    class LAZZO_API Mesh {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

        void Draw(const glm::mat4& modelMatrix, const Lazzo::Object::Camera::Camera& camera, const std::vector<Lazzo::Object::Lights::Light*>& lights);

        glm::vec3& GetColor() { return m_Color; }
        const glm::vec3& GetColor() const { return m_Color; }
        void SetColor(const glm::vec3& color) { m_Color = color; }

        const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
        const std::vector<unsigned int>& GetIndices() const { return m_Indices; }

    private:
        void SetupMesh();

        std::vector<Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;
        glm::vec3 m_Color{ 1.0f, 1.0f, 1.0f };

        std::unique_ptr<Lazzo::Graphics::Material> m_Material;
        std::unique_ptr<Lazzo::Graphics::VertexBuffer> m_VertexBuffer;
        std::unique_ptr<Lazzo::Graphics::IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Lazzo::Graphics::VertexArray> m_VertexArray;
        std::unique_ptr<Lazzo::Graphics::Renderer> m_Renderer;
    };
}