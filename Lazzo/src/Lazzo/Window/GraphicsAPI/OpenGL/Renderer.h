#pragma once
#include "Lazzo/Window/GraphicsAPI/Renderer.h"

namespace Lazzo::Graphics::OpenGL {
    class OpenGLRenderer : public Renderer
    {
    public:
        void Draw(const VertexArray& vao, const VertexBuffer& vbo,
            const IndexBuffer& ibo, const Shader& shader) override;
    };
}
