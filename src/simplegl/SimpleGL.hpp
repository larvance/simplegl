#pragma once
#include <chrono>
#include <fstream>
#include <stdexcept>
#include <GLFW/glfw3.h>

inline bool AllowUnbind = false;

class SimpleGL {
    static inline int ref = 0;

public:
    static void Init() {
        ref++;
        if (ref == 1) {
            if (!glfwInit()) {
                std::cerr << "Failed to init GLFW" << std::endl;
                exit(-1);
            }
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }
    }

    static void Close() {
        if (ref == 0) return;
        ref--;
        if (ref == 0) glfwTerminate();
    }

    static std::string ReadFile(const char* path) {
        std::ifstream file(path);
        if (!file.is_open()) throw std::runtime_error("Could not open file.");
        return std::string((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>());
    }

    static double Time() {
        return glfwGetTime();
    }

    static const unsigned char* Version() {
        return glGetString(GL_VERSION);
    }
};
