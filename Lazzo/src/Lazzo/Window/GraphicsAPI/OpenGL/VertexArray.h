#pragma once
#include <glad/glad.h>
#include "Lazzo/Window/GraphicsAPI/VertexArray.h"

namespace Lazzo::OpenGL {
    class VertexArray:public Lazzo::Graphics::VertexArray {
    private:
        unsigned int m_RendererID{};
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void UnBind() const;

        void AddBuffer(const Lazzo::Graphics::VertexBuffer& vb, const Lazzo::Graphics::VertexBufferLayout& layout) override;
    };
}
