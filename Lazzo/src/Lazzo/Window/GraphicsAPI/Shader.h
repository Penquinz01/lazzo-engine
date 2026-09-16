#pragma once
#include <memory>
#include <string>
#include <glm/glm.hpp>

namespace Lazzo::Graphics {
    class Shader {
    public:
        virtual ~Shader() = default;
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        virtual void SetInt(const std::string& name, int value) const = 0;
        virtual void SetFloat(const std::string& name, float value) const = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& matrix) const = 0;
        virtual void SetFloat2(const std::string& name, const glm::vec2& vector) const = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& vector) const = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& vector) const = 0;

        // OpenGL is the only backend currently supported by this factory.
        static std::unique_ptr<Shader> Create(const std::string& vertexPath, const std::string& fragmentPath);
    };
}
