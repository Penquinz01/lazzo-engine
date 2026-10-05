#include "lzpch.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Texture.h"
#include "Lazzo/Log.h"

namespace Lazzo::OpenGL {

    static const unsigned char s_FallbackPixel[4] = { 255, 0, 255, 255 };

    Texture::Texture(const std::string& path) : m_Path(path) {
        stbi_set_flip_vertically_on_load(0);
        int channels = 0;
        unsigned char* pixels = stbi_load(path.c_str(), &m_Width, &m_Height, &channels, 0);
        if (!pixels) {
            LZ_CORE_ERROR("Failed to load texture '{0}': {1}", path, stbi_failure_reason());
            m_Width = 1;
            m_Height = 1;
            Upload(s_FallbackPixel, 1, 1, 4);
            return;
        }
        Upload(pixels, m_Width, m_Height, channels);
        stbi_image_free(pixels);
        m_IsValid = true;
    }

    Texture::Texture(const void* data, int dataSize, const std::string& debugName)
        : m_Path(debugName) {
        stbi_set_flip_vertically_on_load(0);
        int channels = 0;
        unsigned char* pixels = stbi_load_from_memory(
            static_cast<const stbi_uc*>(data), dataSize, &m_Width, &m_Height, &channels, 0);
        if (!pixels) {
            LZ_CORE_ERROR("Failed to decode embedded texture '{0}': {1}", debugName, stbi_failure_reason());
            m_Width = 1;
            m_Height = 1;
            Upload(s_FallbackPixel, 1, 1, 4);
            return;
        }
        Upload(pixels, m_Width, m_Height, channels);
        stbi_image_free(pixels);
        m_IsValid = true;
    }

    Texture::~Texture() {
        if (m_RendererID)
            glDeleteTextures(1, &m_RendererID);
    }

    void Texture::Bind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void Texture::UnBind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::Upload(const unsigned char* pixels, int width, int height, int channels) {
        GLenum format = GL_RGBA;
        switch (channels) {
            case 1: format = GL_RED; break;
            case 2: format = GL_RG;  break;
            case 3: format = GL_RGB; break;
            case 4: format = GL_RGBA; break;
            default: break;
        }

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

std::unique_ptr<Lazzo::Graphics::Texture> Lazzo::Graphics::Texture::Create(const std::string& path) {
    return std::make_unique<Lazzo::OpenGL::Texture>(path);
}

std::unique_ptr<Lazzo::Graphics::Texture> Lazzo::Graphics::Texture::CreateFromMemory(
    const void* data, int dataSize, const std::string& debugName) {
    return std::make_unique<Lazzo::OpenGL::Texture>(data, dataSize, debugName);
}
