 #pragma once
#include <glad/glad.h>
namespace Lazzo::OpenGL {
    class VertexBuffer {
    private:
        unsigned int m_RendererID;
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();
        void Bind() const;
        void UnBind() const;
    };
}