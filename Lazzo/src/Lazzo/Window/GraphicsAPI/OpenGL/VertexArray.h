#pragma once
#include <glad/glad.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Lazzo {
    class VertexArray {
    private:
        unsigned int m_RendererID{};
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void UnBind() const;

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    };
}