#include "lzpch.h"
#include "VertexBuffer.h"

namespace Lazzo::OpenGL {
    VertexBuffer::VertexBuffer(const void* data, unsigned int stride) {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, stride, data, GL_STATIC_DRAW);
    }
    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }
    
    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }
    void VertexBuffer::Unbind() const{
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

std::unique_ptr<Lazzo::Graphics::VertexBuffer> Lazzo::Graphics::VertexBuffer::Create(const void* data, uint32_t size) {
    return std::make_unique<Lazzo::OpenGL::VertexBuffer>(data, size);
}
