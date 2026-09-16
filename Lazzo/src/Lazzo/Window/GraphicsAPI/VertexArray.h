#pragma once
#include <memory>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Lazzo::Graphics {
    
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        virtual void AddBuffer(const Lazzo::Graphics::VertexBuffer& vb, const VertexBufferLayout& layout) = 0;
        static std::unique_ptr<VertexArray> Create();
    };
}
