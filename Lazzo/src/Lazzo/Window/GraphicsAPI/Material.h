#pragma once

#include "Shader.h"

namespace Lazzo::Graphics {
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

    private:
        std::unique_ptr<Shader> m_Shader;
    };
}
