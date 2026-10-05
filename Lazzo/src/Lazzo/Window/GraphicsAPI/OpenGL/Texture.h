 #pragma once
#include <glad/glad.h>
#include <string>
#include "Lazzo/Window/GraphicsAPI/Texture.h"

namespace Lazzo::OpenGL {
    class Texture : public Lazzo::Graphics::Texture {
    public:
        explicit Texture(const std::string& path);
        Texture(const void* data, int dataSize, const std::string& debugName);
        ~Texture() override;

        void Bind(unsigned int slot = 0) const override;
        void UnBind() const override;

        unsigned int GetWidth() const override { return m_Width; }
        unsigned int GetHeight() const override { return m_Height; }
        const std::string& GetPath() const override { return m_Path; }
        bool IsValid() const override { return m_IsValid; }

    private:
        void Upload(const unsigned char* pixels, int width, int height, int channels);

        unsigned int m_RendererID = 0;
        int m_Width = 0;
        int m_Height = 0;
        std::string m_Path;
        bool m_IsValid = false;
    };
}
