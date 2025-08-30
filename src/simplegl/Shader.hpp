#pragma once
#include <glad/glad.h>

#include "SimpleGL.hpp"
#include <glm/glm.hpp>

#include "UniformVariable.hpp"

class Shader {
    void Init(const char* vertSource, const char* fragSource) {
        GLuint vert = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vert, 1, &vertSource, nullptr);
        glCompileShader(vert);
        HandleShaderCompileErrors(vert, "VERTEX");
        GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag, 1, &fragSource, nullptr);
        glCompileShader(frag);
        HandleShaderCompileErrors(frag, "FRAGMENT");
        ID = glCreateProgram();
        glAttachShader(ID, vert);
        glAttachShader(ID, frag);
        glLinkProgram(ID);
        HandleProgramCompileErrors(frag);
        glDeleteShader(vert);
        glDeleteShader(frag);
    }

public:
    GLuint ID;

    Shader(const char* vertSource, const char* fragSource) {
        Init(vertSource, fragSource);
    }

    Shader(const std::string& vertSource, const std::string& fragSource) {
        Init(vertSource.c_str(), fragSource.c_str());
    }

    explicit Shader(const char* basePath) {
        std::string vertPath = std::string(basePath) + ".vert";
        std::string fragPath = std::string(basePath) + ".frag";

        std::string vertSource = SimpleGL::ReadFile(vertPath.c_str());
        std::string fragSource = SimpleGL::ReadFile(fragPath.c_str());

        Init(vertSource.c_str(), fragSource.c_str());
    }

    GLint GetUniformLocation(const char* name) const {
        return glGetUniformLocation(ID, name);
    }

    template <typename T>
    UniformVariable<T> GetUniform(const char* name) const {
        return UniformVariable<T>(GetUniformLocation(name));
    }

    template <typename T>
    void SetUniform(const char* name, T v) const {
        UniformVariable<T>::SetUniformImpl(GetUniformLocation(name), v);
    }

    template <typename T>
    void SetUniform(GLint location, T v) const {
        UniformVariable<T>::SetUniformImpl(location, v);
    }

    void Activate() const {
        glUseProgram(ID);
    }

    ~Shader() {
        glDeleteProgram(ID);
    }

private:
    static void HandleShaderCompileErrors(unsigned int shader, const char* type) {
        GLint hasCompiled;
        char infoLog[1024];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE) {
            glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << infoLog << std::endl;
        }
    }

    static void HandleProgramCompileErrors(unsigned int shader) {
        GLint hasCompiled;
        char infoLog[1024];
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE) {
            glGetProgramInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
            std::cout << "SHADER_LINKING_ERROR for: PROGRAM" << "\n" << infoLog << std::endl;
        }
    }
};
