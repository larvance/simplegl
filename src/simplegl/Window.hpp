#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SimpleGL.hpp"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

class Window final {
    static void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
        glViewport(0, 0, w, h);

        auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (self) {
            self->width = w;
            self->height = h;
        }
    }

public:
    GLFWwindow* window;
    int width, height;
    bool destroyed = false;
    bool depthTest = false;

    Window(int w, int h, const char* title) : width(w), height(h) {
        SimpleGL::Init();
        window = glfwCreateWindow(w, h, title, nullptr, nullptr);
        if (!window) {
            std::cout << "Window could not be opened." << std::endl;
            exit(-1);
        }
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            std::cerr << "Failed to initialize GLAD\n";
            exit(-1);
        }
    }

    [[nodiscard]] bool DepthTest() const {
        return depthTest;
    }

    void SetDepthTest(bool value) {
        if (value == depthTest) return;
        depthTest = value;
        if (!value) {
            glDisable(GL_DEPTH_TEST);
        } else {
            glEnable(GL_DEPTH_TEST);
        }
    }

    int Width() const {
        return width;
    }

    int Height() const {
        return height;
    }

    float AspectRatio() const {
        return static_cast<float>(width) / static_cast<float>(height);
    }

    void SwapBuffers() const {
        glfwSwapBuffers(window);
    }

    static void Poll() {
        glfwPollEvents();
    };

    bool ShouldClose() const {
        return glfwWindowShouldClose(window);
    }

    void Render() const {
        SwapBuffers();
        Poll();
    }

    const char* Title() const {
        return glfwGetWindowTitle(window);
    }

    void Title(const char* title) const {
        glfwSetWindowTitle(window, title);
    }

    void Title(const std::string& title) const {
        glfwSetWindowTitle(window, title.c_str());
    }

    void ClearBackground(float r, float g, float b, float a = 1.0) const {
        glClearColor(r, g, b, a);
        glClear(depthTest ? GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT : GL_COLOR_BUFFER_BIT);
    }

    bool IsKeyPressed(int key) const {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

    bool IsKeyReleased(int key) const {
        return glfwGetKey(window, key) == GLFW_RELEASE;
    }

    bool IsMouseButtonPressed(int button) const {
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    bool IsMouseButtonReleased(int button) const {
        return glfwGetMouseButton(window, button) == GLFW_RELEASE;
    }

    void HideCursor() const {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void ShowCursor() const {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void CenterCursor() const {
        glfwSetCursorPos(window, width / 2.0, height / 2.0);
    }

    void SetCursorPos(double x, double y) const {
        glfwSetCursorPos(window, x, y);
    }

    void CursorPos(double& x, double& y) const {
        glfwGetCursorPos(window, &x, &y);
    }

    glm::dvec2 CursorPos() const {
        glm::dvec2 pos;
        glfwGetCursorPos(window, &pos.x, &pos.y);
        return pos;
    }

    void Close() {
        if (destroyed) return;
        destroyed = true;
        glfwDestroyWindow(window);
        SimpleGL::Close();
    }

    ~Window() {
        Close();
    }
};
