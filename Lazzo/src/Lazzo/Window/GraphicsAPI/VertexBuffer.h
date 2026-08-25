#pragma once
#include <memory>
#include "OpenGL/OpenGL.h"

namespace Lazzo::Graphics {
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static std::unique_ptr<VertexBuffer> Create(const void* data, uint32_t size) {
            return std::make_unique<Lazzo::OpenGL::VertexBuffer>(data, size);
        }
    };
}
