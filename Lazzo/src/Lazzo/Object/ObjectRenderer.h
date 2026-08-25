#pragma once
#include "Lazzo/Window/GraphicsAPI/GraphicsAPI.h"

using namespace  Lazzo::Graphics;
namespace Lazzo::Object {
    

    class ObjectRenderer
    {
    public:
        ObjectRenderer(float* vertices, size_t vertexCount,VertexBufferLayout layout,ShaderFileData shaderData);
        ObjectRenderer(float* vertices, size_t vertexCount, VertexBufferLayout layout, unsigned int* indices, size_t indexCount,ShaderFileData shaderData);
        void Draw();
    private:
        std::unique_ptr<Renderer> m_Renderer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<VertexArray> m_VertexArray;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<Shader> m_Shader;

        bool hasIndexBuffer;
    };
}

