#include "lzpch.h"
#include "VertexArray.h"

namespace Lazzo::OpenGL {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &m_RendererID);
    }
    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::Bind() const {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::UnBind() const {
        glBindVertexArray(0);
    }
    
    void VertexArray::AddBuffer(const Lazzo::Graphics::VertexBuffer& vb, const Lazzo::Graphics::VertexBufferLayout& layout) {
        Bind();
        vb.Bind();
        const auto& elements = layout.getElements();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++) {
            const auto& element = elements[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
            offset += element.count * Lazzo::Graphics::VertexBufferElement::getSizeOfType(element.type);
        }
    }
}

std::unique_ptr<Lazzo::Graphics::VertexArray> Lazzo::Graphics::VertexArray::Create() {
    return std::make_unique<Lazzo::OpenGL::VertexArray>();
}
