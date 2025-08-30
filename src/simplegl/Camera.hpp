#pragma once
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.hpp"
#include "Window.hpp"

class Camera {
public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    float fov = glm::radians(45.0f);
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    const Window& window;

    explicit Camera(const Window& window) : window(window) {
    }

    glm::mat4 Matrix() const {
        auto view = glm::lookAt(position, position + orientation, up);
        auto projection = glm::perspective(fov, window.AspectRatio(), nearPlane, farPlane);

        return projection * view;
    }

    void Matrix(const Shader& shader) const {
        shader.SetUniform("camMatrix", Matrix());
    }
};
