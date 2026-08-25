#pragma once
#include <memory>
#include "OpenGL/OpenGL.h"
#include <string>

namespace Lazzo::Graphics {
    class Shader {
    public:
        virtual void SetInt(const std::string& name, int value) const = 0;
        virtual void SetFloat(const std::string& name, float value) const = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& matrix) const = 0;
        virtual void SetFloat2(const std::string& name, const glm::vec2& vector) const = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& vector) const = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& vector) const = 0;

        static std::unique_ptr<Shader> Create(const std::string& vertexPath, const std::string& fragmentPath) {
            return std::make_unique<Lazzo::OpenGL::Shader>(vertexPath, fragmentPath);
        }
    };
}
