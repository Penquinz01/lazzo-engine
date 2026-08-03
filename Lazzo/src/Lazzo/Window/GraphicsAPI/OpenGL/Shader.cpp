#include "lzpch.h"
#include "Shader.h"
#include <Lazzo/Log.h>

namespace Lazzo {
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) : vertexSourcePath(vertexPath), fragmentSourcePath(fragmentPath) {

        m_RendererID = CreateShader(vertexSourcePath, fragmentSourcePath);
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
}