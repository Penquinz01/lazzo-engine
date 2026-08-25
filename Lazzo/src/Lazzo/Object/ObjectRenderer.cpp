#include "lzpch.h"
#include "ObjectRenderer.h"
#include "Lazzo/Utilities/Utilities.h"

namespace Lazzo::Object {
    ObjectRenderer::ObjectRenderer(float* vertices, size_t vertexCount, VertexBufferLayout layout, ShaderFileData shaderData) {
        m_Renderer = Lazzo::Graphics::Renderer::Create();
        m_VertexBuffer = Lazzo::Graphics::VertexBuffer::Create(vertices, vertexCount * sizeof(float));
        m_VertexArray = Lazzo::Graphics::VertexArray::Create();
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
        m_Shader = Lazzo::Graphics::Shader::Create(shaderData.vertexSourcePath, shaderData.fragmentSourcePath);
        hasIndexBuffer = false;
    }
}
