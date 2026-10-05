#include "lzpch.h"
#include "Material.h"

namespace Lazzo::Graphics {

    namespace {
        struct TextureBinding {
            const char* samplerName;
            const char* flagName;
            unsigned int unit;
        };

        constexpr std::array<TextureBinding, static_cast<size_t>(TextureSlot::Count)> s_Bindings = { {
            { "u_AlbedoMap",   "u_UseAlbedoMap",   0 },
            { "u_NormalMap",   "u_UseNormalMap",   1 },
            { "u_SpecularMap", "u_UseSpecularMap", 2 },
            { "u_RoughnessMap","u_UseRoughnessMap",3 },
            { "u_AOMap",       "u_UseAOMap",       4 },
        } };
    }

    void Material::BindTextures() const {
        for (size_t i = 0; i < m_Textures.size(); i++) {
            const auto& binding = s_Bindings[i];
            const auto& texture = m_Textures[i];
            if (texture) {
                texture->Bind(binding.unit);
                m_Shader->SetInt(binding.samplerName, static_cast<int>(binding.unit));
                m_Shader->SetInt(binding.flagName, 1);
            }
            else {
                m_Shader->SetInt(binding.flagName, 0);
            }
        }
    }
}
