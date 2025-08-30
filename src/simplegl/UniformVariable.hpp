#pragma once
#include <glad/glad.h>

template <typename T>
class UniformVariable {
public:
    GLint location;

    explicit UniformVariable(GLint loc) : location(loc) {
    }

    void Set(T v) const {
        SetUniformImpl(location, v);
    }

    static void SetUniformImpl(GLint loc, GLdouble v) {
        glUniform1d(loc, v);
    }

    static void SetUniformImpl(GLint loc, GLfloat v) {
        glUniform1f(loc, v);
    }

    static void SetUniformImpl(GLint loc, GLint v) {
        glUniform1i(loc, v);
    }

    static void SetUniformImpl(GLint loc, GLuint v) {
        glUniform1ui(loc, v);
    }

    static void SetUniformImpl(GLint loc, const glm::dvec2& v) {
        glUniform2d(loc, v.x, v.y);
    }

    static void SetUniformImpl(GLint loc, const glm::fvec2& v) {
        glUniform2f(loc, v.x, v.y);
    }

    static void SetUniformImpl(GLint loc, const glm::ivec2& v) {
        glUniform2i(loc, v.x, v.y);
    }

    static void SetUniformImpl(GLint loc, const glm::uvec2& v) {
        glUniform2ui(loc, v.x, v.y);
    }

    static void SetUniformImpl(GLint loc, const glm::dvec3& v) {
        glUniform3d(loc, v.x, v.y, v.z);
    }

    static void SetUniformImpl(GLint loc, const glm::fvec3& v) {
        glUniform3f(loc, v.x, v.y, v.z);
    }

    static void SetUniformImpl(GLint loc, const glm::ivec3& v) {
        glUniform3i(loc, v.x, v.y, v.z);
    }

    static void SetUniformImpl(GLint loc, const glm::uvec3& v) {
        glUniform3ui(loc, v.x, v.y, v.z);
    }

    static void SetUniformImpl(GLint loc, const glm::dvec4& v) {
        glUniform4d(loc, v.x, v.y, v.z, v.w);
    }

    static void SetUniformImpl(GLint loc, const glm::fvec4& v) {
        glUniform4f(loc, v.x, v.y, v.z, v.w);
    }

    static void SetUniformImpl(GLint loc, const glm::ivec4& v) {
        glUniform4i(loc, v.x, v.y, v.z, v.w);
    }

    static void SetUniformImpl(GLint loc, const glm::uvec4& v) {
        glUniform4ui(loc, v.x, v.y, v.z, v.w);
    }

    static void SetUniformImpl(GLint loc, const glm::dmat2& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix2dv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::fmat2& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix2fv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::dmat2x3& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix2x3dv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::fmat2x3& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix2x3fv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::dmat2x4& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix2x4dv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::fmat2x4& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix2x4fv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::dmat3& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix3dv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::fmat3& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix3fv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::dmat3x2& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix3x2dv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::fmat3x2& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix3x2fv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::dmat3x4& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix3x4dv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::fmat3x4& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix3x4fv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::dmat4& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix4dv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::fmat4& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix4fv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::dmat4x2& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix4x2dv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::fmat4x2& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix4x2fv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::dmat4x3& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix4x3dv(loc, 1, transpose, &v[0][0]);
    }

    static void SetUniformImpl(GLint loc, const glm::fmat4x3& v, GLboolean transpose = GL_FALSE) {
        glUniformMatrix4x3fv(loc, 1, transpose, &v[0][0]);
    }
};
