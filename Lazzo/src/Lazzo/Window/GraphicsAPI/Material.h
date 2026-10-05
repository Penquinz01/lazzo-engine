#pragma once

#include <array>
#include <memory>
#include "Shader.h"
#include "Texture.h"

namespace Lazzo::Graphics {

    // Fixed texture slots matching the sampler/flag pairs declared in Basic.frag.
    enum class TextureSlot : size_t {
        Albedo = 0,
        Normal,
        Specular,
        Roughness,
        AO,
        Count
    };

    // A material owns the program used to render a primitive and is the public
    // place where its shader uniforms are changed.
    class Material {
    public:
        Material(const std::string& vertexPath, const std::string& fragmentPath)
            : m_Shader(Shader::Create(vertexPath, fragmentPath)) {}

        void Bind() const { m_Shader->Bind(); }
        void UnBind() const { m_Shader->UnBind(); }

        void SetInt(const std::string& name, int value) const { m_Shader->SetInt(name, value); }
        void SetFloat(const std::string& name, float value) const { m_Shader->SetFloat(name, value); }
        void SetMat4(const std::string& name, const glm::mat4& value) const { m_Shader->SetMat4(name, value); }
        void SetFloat2(const std::string& name, const glm::vec2& value) const { m_Shader->SetFloat2(name, value); }
        void SetFloat3(const std::string& name, const glm::vec3& value) const { m_Shader->SetFloat3(name, value); }
        void SetFloat4(const std::string& name, const glm::vec4& value) const { m_Shader->SetFloat4(name, value); }

        void SetTexture(TextureSlot slot, std::shared_ptr<Texture> texture) {
            m_Textures[static_cast<size_t>(slot)] = std::move(texture);
        }

        // Binds every assigned texture to its fixed unit, sets the sampler
        // uniform, and toggles the matching u_Use*Map flag. Call after Bind().
        void BindTextures() const;

        const Shader& GetShader() const { return *m_Shader; }

    private:
        std::unique_ptr<Shader> m_Shader;
        std::array<std::shared_ptr<Texture>, static_cast<size_t>(TextureSlot::Count)> m_Textures{};
    };
}
