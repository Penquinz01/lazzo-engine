#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include "Lazzo/Window/GraphicsAPI/GraphicsAPI.h"

namespace Lazzo::OpenGL {
    class Shader : public Lazzo::Graphics::Shader
    {
    private:
        unsigned int m_RendererID;
        std::string vertexSourcePath;
        std::string fragmentSourcePath;

        std::unordered_map<std::string,int> m_UniformLocationCache;
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();
        void Bind() const;
        void UnBind() const;
    private:
        unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource);
        unsigned int CompileShader(unsigned int type, const std::string& source);


        int GetUniformLocation(const std::string& name) const;
    public:
            void SetInt(const std::string& name, int value) const override;
            void SetFloat(const std::string& name, float value) const override;
            void SetMat4(const std::string& name, const glm::mat4& matrix) const override;
            void SetFloat2(const std::string& name, const glm::vec2& vector) const override;
            void SetFloat3(const std::string& name, const glm::vec3& vector) const override;
            void SetFloat4(const std::string& name, const glm::vec4& vector) const override;
    };
}

