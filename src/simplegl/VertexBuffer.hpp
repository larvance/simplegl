#pragma once
#include <glad/glad.h>

#include "Layout.hpp"
#include "VertexArray.hpp"

class VertexBuffer {
public:
    GLuint ID;
    const VertexArray& vao;
    int amount{};

    template <size_t N>
    VertexBuffer(const VertexArray& vao, const GLfloat (&arr)[N],
                 std::initializer_list<Layout> layouts) : vao(vao), amount(N) {
        vao.Bind();
        glGenBuffers(1, &ID);

        Bind();
        // stream: modified once, used a few times
        // static: modified once, used many times
        // dynamic: modified multiple times, used many times
        // draw: vertices will be modified and will be used to draw
        // copy: vertices will be modified and used by the GPU
        // read: vertices will be modified by the GPU and used by the CPU
        glBufferData(GL_ARRAY_BUFFER, N * sizeof(float), arr, GL_STATIC_DRAW);

        int stride = 0;
        for (const auto& layout : layouts) {
            stride += layout.size;
        }

        size_t offset = 0;
        int index = 0;
        for (const auto& layout : layouts) {
            glVertexAttribPointer(
                index, layout.count, static_cast<GLenum>(layout.type),
                layout.normalized, stride, reinterpret_cast<void*>(offset)
            );
            glEnableVertexAttribArray(index);
            offset += layout.size;
            index++;
        }
        Unbind();
        vao.Unbind();
    }

    void Draw(int start = 0) const {
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, start, amount);
        vao.Unbind();
    }

    void Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    static void Unbind() {
        if (AllowUnbind) {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }

    ~VertexBuffer() {
        glDeleteBuffers(1, &ID);
    }
};
