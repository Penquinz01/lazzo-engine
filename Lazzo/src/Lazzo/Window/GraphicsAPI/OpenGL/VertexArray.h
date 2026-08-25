#pragma once
#include <glad/glad.h>
#include "VertexBuffer.h"
#include "Lazzo/Window/GraphicsAPI/GraphicsAPI.h"

namespace Lazzo::OpenGL {
    class VertexArray:public Lazzo::Graphics::VertexArray {
    private:
        unsigned int m_RendererID{};
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void UnBind() const;

        void AddBuffer(const VertexBuffer& vb, const Lazzo::Graphics::VertexBufferLayout& layout);
    };
}