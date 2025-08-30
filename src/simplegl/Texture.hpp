#pragma once
#include <iostream>
#include <glad/glad.h>

#include "SimpleGL.hpp"
#include "stb/stb_image.h"

class Texture {
public:
    GLuint ID;
    int width;
    int height;
    int numChannels;

    explicit Texture(const char* path) {
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path, &width, &height, &numChannels, 0);

        if (!data) {
            std::cerr << "Failed to load texture: " << path << std::endl;
            exit(-1);
        }

        glGenTextures(1, &ID);
        Bind();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        GLenum format = numChannels == 4 ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        Unbind();
    }

    void Bind() const {
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    static void Unbind() {
        if (AllowUnbind) {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    void Activate() const {
        glActiveTexture(GL_TEXTURE0);
        Bind();
    }
};
