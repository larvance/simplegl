#pragma once
#include <glad/glad.h>

#include "SimpleGL.hpp"
#include "VertexArray.hpp"

class ElementBuffer {
public:
    GLuint ID;
    const VertexArray& vao;
    int amount{};

    explicit ElementBuffer(const VertexArray& vao) : vao(vao) {
        glGenBuffers(1, &ID);
    }

    ElementBuffer(const VertexArray& vao, const GLuint* arr, int size) : ElementBuffer(vao) {
        Link(arr, size);
    }

    template <size_t N>
    explicit ElementBuffer(const VertexArray& vao, const GLuint (&arr)[N]) : ElementBuffer(vao, arr, N * sizeof(GLuint)) {
    }

    void Draw(const void* indices = nullptr) const {
        vao.Bind();
        Bind();
        glDrawElements(GL_TRIANGLES, amount / sizeof(GLuint), GL_UNSIGNED_INT, indices);
        Unbind();
        vao.Unbind();
    }

    void Link(const GLuint* arr, int size) {
        amount = size;
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, arr, GL_STATIC_DRAW);
        Unbind();
    }

    void Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    static void Unbind() {
        if (AllowUnbind) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }

    ~ElementBuffer() {
        glDeleteBuffers(1, &ID);
    }
};
