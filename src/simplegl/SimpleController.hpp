#pragma once
#include <GLFW/glfw3.h>
#include <glm/gtx/vector_angle.hpp>

#include "Camera.hpp"
#include "Window.hpp"

class Window;

class SimpleController {
public:
    Camera& camera;
    float speed = 0.1f;
    float sensitivity = 100.0f;
    bool firstClick = true;

    explicit SimpleController(Camera& camera) : camera(camera) {
    }

    void Update() {
        auto& window = camera.window;
        if (window.IsKeyPressed(GLFW_KEY_W)) {
            camera.position += speed * camera.orientation;
        }
        if (window.IsKeyPressed(GLFW_KEY_A)) {
            camera.position += speed * -glm::normalize(glm::cross(camera.orientation, camera.up));
        }
        if (window.IsKeyPressed(GLFW_KEY_S)) {
            camera.position += speed * -camera.orientation;
        }
        if (window.IsKeyPressed(GLFW_KEY_D)) {
            camera.position += speed * glm::normalize(glm::cross(camera.orientation, camera.up));
        }
        if (window.IsKeyPressed(GLFW_KEY_SPACE)) {
            camera.position += speed * camera.up;
        }
        if (window.IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
            camera.position += speed * -camera.up;
        }
        if (window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
            speed = 0.4f;
        } else if (window.IsKeyReleased(GLFW_KEY_LEFT_SHIFT)) {
            speed = 0.1f;
        }


        if (window.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            window.HideCursor();

            if (firstClick) {
                window.CenterCursor();
                firstClick = false;
            }

            auto mouse = window.CursorPos();

            float rotX = sensitivity * static_cast<float>(mouse.y - (window.height / 2)) / window.height;
            float rotY = sensitivity * static_cast<float>(mouse.x - (window.width / 2)) / window.width;

            glm::vec3 newOrientation = glm::rotate(camera.orientation, glm::radians(-rotX),
                                                   glm::normalize(glm::cross(camera.orientation, camera.up)));

            if (abs(glm::angle(newOrientation, camera.up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
                camera.orientation = newOrientation;
            }

            camera.orientation = glm::rotate(camera.orientation, glm::radians(-rotY), camera.up);

            window.CenterCursor();
        } else if (window.IsMouseButtonReleased(GLFW_MOUSE_BUTTON_LEFT)) {
            window.ShowCursor();
            firstClick = true;
        }
    }
};
