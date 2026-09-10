#include "lzpch.h"
#include "Renderer.h"

namespace Lazzo::Graphics::OpenGL {
    void OpenGLRenderer::Draw(const VertexArray&, const VertexBuffer&, const IndexBuffer&, const Shader&) {
    }
}

std::unique_ptr<Lazzo::Graphics::Renderer> Lazzo::Graphics::Renderer::Create() {
    return std::make_unique<Lazzo::Graphics::OpenGL::OpenGLRenderer>();
}
