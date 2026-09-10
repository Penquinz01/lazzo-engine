#pragma once
#include <memory>

namespace Lazzo::Graphics {
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    class Shader;
}

namespace Lazzo::Graphics {
    class Renderer
    {
    public:
        virtual ~Renderer() = default;
        virtual void Draw(const VertexArray& vao, const VertexBuffer& vbo,
            const IndexBuffer& ibo, const Shader& shader) = 0;

        static std::unique_ptr<Renderer> Create();
    };
}
