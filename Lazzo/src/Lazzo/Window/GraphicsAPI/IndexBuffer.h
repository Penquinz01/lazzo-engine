#pragma once
#include <memory>

namespace Lazzo::Graphics {
    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        static std::unique_ptr<IndexBuffer> Create(const unsigned int* data, unsigned int count);
    };
}
