#include "lzpch.h"
#include "Shader.h"
#include <Lazzo/Log.h>

namespace Lazzo::OpenGL {
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) : vertexSourcePath(vertexPath), fragmentSourcePath(fragmentPath) {
        m_RendererID = CreateShader(ReadShaderFile(vertexSourcePath), ReadShaderFile(fragmentSourcePath));
    }
    Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }
    void Shader::Bind() const {
        glUseProgram(m_RendererID);
    }
    void Shader::UnBind() const {
        glUseProgram(0);
    }

    std::string Shader::ReadShaderFile(const std::string& path) {
        std::ifstream stream(path);
        if (!stream.is_open()) {
            LZ_CORE_ERROR("Failed to open shader file: {0}", path);
            return {};
        }

        std::stringstream source;
        source << stream.rdbuf();
        return source.str();
    }

    unsigned int Shader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource) {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);
        return program;
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (!result) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            std::string log(length, ' ');
            glGetShaderInfoLog(id, length, nullptr, log.data());
            LZ_CORE_ERROR("Failed to compile {0} shader:\n{1}", type == GL_VERTEX_SHADER ? "vertex" : "fragment", log);
            return 0;
        }
        return id;
    }
    int Shader::GetUniformLocation(const std::string& name) const {
        return glGetUniformLocation(m_RendererID, name.c_str());
    }
    void Lazzo::OpenGL::Shader::SetInt(const std::string& name, int value) const {
        glUniform1i(GetUniformLocation(name), value);
    }
    void Lazzo::OpenGL::Shader::SetFloat(const std::string& name, float value) const {
        glUniform1f(GetUniformLocation(name), value);
    }
    void Lazzo::OpenGL::Shader::SetMat4(const std::string& name, const glm::mat4& matrix) const {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }
    void Lazzo::OpenGL::Shader::SetFloat2(const std::string& name, const glm::vec2& vector) const {
        glUniform2f(GetUniformLocation(name), vector.x, vector.y);
    }
    void Lazzo::OpenGL::Shader::SetFloat3(const std::string& name, const glm::vec3& vector) const {
        glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
    }
    void Lazzo::OpenGL::Shader::SetFloat4(const std::string& name, const glm::vec4& vector) const {
        glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
    }
}

std::unique_ptr<Lazzo::Graphics::Shader> Lazzo::Graphics::Shader::Create(
    const std::string& vertexPath, const std::string& fragmentPath) {
    return std::make_unique<Lazzo::OpenGL::Shader>(vertexPath, fragmentPath);
}
