#pragma once
#include <glad/glad.h>
#include "SimpleGL.hpp"

class VertexArray {
public:
    GLuint ID;

    VertexArray() {
        glGenVertexArrays(1, &ID);
    }

    void Bind() const {
        glBindVertexArray(ID);
    }

    static void Unbind() {
        if (AllowUnbind) {
            glBindVertexArray(0);
        }
    }

    ~VertexArray() {
        glDeleteVertexArrays(1, &ID);
    }
};
