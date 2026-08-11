#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

namespace Lazzo::OpenGL {
    class Shader
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


        int GetUniformLocation(const std::string& name);
    public:
        template<typename T>
        void SetUniform(const std::string& name, const T& value) {
            int location = GetUniformLocation(name);
            if constexpr (std::is_same_v<T, float>) {
                glUniform1f(location, value);
            }
            else if constexpr (std::is_same_v<T, int>) {
                glUniform1i(location, value);
            }
            else if constexpr (std::is_same_v<T, glm::vec2>) {
                glUniform2f(location, value.x, value.y);
            }
            else if constexpr (std::is_same_v<T, glm::vec3>) {
                glUniform3f(location, value.x, value.y, value.z);
            }
            else if constexpr (std::is_same_v<T, glm::vec4>) {
                glUniform4f(location, value.x, value.y, value.z, value.w);
            }
            else if constexpr (std::is_same_v<T, glm::mat4>) {
                glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
            }
        }
    };
}

