#pragma once
#include <glad/glad.h>
#include "Lazzo/Window/GraphicsAPI/IndexBuffer.h"

namespace Lazzo::OpenGL {
    class IndexBuffer :public Lazzo::Graphics::IndexBuffer
    {
    private:
        unsigned int m_RendererID;
        unsigned int m_Count;
    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void UnBind() const;

        inline unsigned int getCount() const { return m_Count; }
    };
}

