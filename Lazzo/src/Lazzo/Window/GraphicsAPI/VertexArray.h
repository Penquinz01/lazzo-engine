#pragma once
#include <memory>
#include "OpenGL/OpenGL.h"
#include "GraphicsAPI.h"

namespace Lazzo::Graphics {
    
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void AddBuffer(const Lazzo::Graphics::VertexBuffer& vb, const VertexBufferLayout& layout) = 0;
        static std::unique_ptr<VertexArray> Create() {
            return std::make_unique<Lazzo::OpenGL::VertexArray>();
        }
    };
}
