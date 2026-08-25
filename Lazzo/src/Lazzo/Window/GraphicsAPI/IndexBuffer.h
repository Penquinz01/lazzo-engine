#pragma once
#include "OpenGL/OpenGL.h"

namespace Lazzo::Graphics {
    class IndexBuffer {
        virtual ~IndexBuffer() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static std::unique_ptr<IndexBuffer> Create(const unsigned int* data, unsigned int count) {
            return std::make_unique<Lazzo::OpenGL::IndexBuffer>(data, count);
        }
    };
}