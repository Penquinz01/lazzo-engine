#include "lzpch.h"
#include "Renderer.h"
#include "Lazzo/Window/GraphicsAPI/IndexBuffer.h"
#include "Lazzo/Window/GraphicsAPI/VertexArray.h"
#include <glad/glad.h>

namespace Lazzo::Graphics::OpenGL {
    void OpenGLRenderer::Draw(const VertexArray& vao, const VertexBuffer&, const IndexBuffer& ibo, const Shader&) {
        vao.Bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(ibo.GetCount()), GL_UNSIGNED_INT, nullptr);
        vao.UnBind();
    }
}

std::unique_ptr<Lazzo::Graphics::Renderer> Lazzo::Graphics::Renderer::Create() {
    return std::make_unique<Lazzo::Graphics::OpenGL::OpenGLRenderer>();
}
