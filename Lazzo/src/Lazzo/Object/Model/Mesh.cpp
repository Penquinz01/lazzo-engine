#include "lzpch.h"
#include "Mesh.h"
#include "Lazzo/Object/Lights/LightUniforms.h"
#include "Lazzo/Window/GraphicsAPI/VertexBufferLayout.h"

namespace Lazzo::Object {

    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
        : m_Vertices(std::move(vertices)), m_Indices(std::move(indices)) {
        SetupMesh();
    }

    void Mesh::SetupMesh() {
        m_Renderer = Lazzo::Graphics::Renderer::Create();
        m_Material = std::make_unique<Lazzo::Graphics::Material>(
            "../Lazzo/Shaders/GLSL/Basic.vert",
            "../Lazzo/Shaders/GLSL/Basic.frag");

        m_VertexBuffer = Lazzo::Graphics::VertexBuffer::Create(
            m_Vertices.data(), static_cast<uint32_t>(m_Vertices.size() * sizeof(Vertex)));
        m_VertexArray = Lazzo::Graphics::VertexArray::Create();

        Lazzo::Graphics::VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = Lazzo::Graphics::IndexBuffer::Create(
            m_Indices.data(), static_cast<unsigned int>(m_Indices.size()));
    }

    void Mesh::Draw(const glm::mat4& modelMatrix, const Lazzo::Object::Camera::Camera& camera, const std::vector<Lazzo::Object::Lights::Light*>& lights) {
        m_Material->Bind();
        m_Material->SetMat4("u_Model", modelMatrix);
        m_Material->SetMat4("u_View", camera.GetViewMatrix());
        m_Material->SetMat4("u_Projection", camera.GetProjectionMatrix());
        m_Material->SetFloat3("u_Color", m_Color);
        m_Material->SetFloat3("u_ViewPos", camera.GetPosition());

        Lazzo::Object::Lights::SetLightUniforms(*m_Material, lights);

        m_Renderer->Draw(*m_VertexArray, *m_VertexBuffer, *m_IndexBuffer, m_Material->GetShader());
    }
}