#pragma once

namespace Lazzo::Graphics {
    class Renderer
    {
    public:
        virtual void Draw(VertexArray vao,VertexBuffer vbo,IndexBuffer ibo,Shader shader) = 0;

        static std::unique_ptr<Renderer> Create() {
            return std::make_unique<Lazzo::Graphics::OpenGL::OpenGLRenderer>();
        }
    };
}