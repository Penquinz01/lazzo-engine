#include "lzpch.h"
#include "IndexBuffer.h"

namespace Lazzo::OpenGL {
    IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_Count(count) {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }
    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }
    void IndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }
    void IndexBuffer::UnBind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

std::unique_ptr<Lazzo::Graphics::IndexBuffer> Lazzo::Graphics::IndexBuffer::Create(const unsigned int* data, unsigned int count) {
    return std::make_unique<Lazzo::OpenGL::IndexBuffer>(data, count);
}
