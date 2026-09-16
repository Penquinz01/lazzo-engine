 #pragma once
#include <glad/glad.h>
#include "Lazzo/Window/GraphicsAPI/VertexBuffer.h"
namespace Lazzo::OpenGL {
    class VertexBuffer: public Lazzo::Graphics::VertexBuffer {
    private:
        unsigned int m_RendererID;
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();
        void Bind() const;
        void Unbind() const;
    };
}
