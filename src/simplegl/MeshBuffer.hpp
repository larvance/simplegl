#pragma once
#include "ElementBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

class MeshBuffer {
public:
    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    ElementBuffer elementBuffer;

    template <size_t N, size_t M>
    MeshBuffer(const GLfloat (&vertices)[N], const GLuint (&indices)[M], std::initializer_list<Layout> layouts)
        : vertexArray(),
          vertexBuffer(vertexArray, vertices, layouts),
          elementBuffer(vertexArray, indices) {
    }


    void Draw() const {
        elementBuffer.Draw();
    }
};
