#include <iostream>
#include <glad/glad.h>

#include "simplegl/Camera.hpp"
#include "simplegl/ElementBuffer.hpp"
#include "simplegl/MeshBuffer.hpp"
#include "simplegl/Shader.hpp"
#include "simplegl/SimpleController.hpp"
#include "simplegl/VertexBuffer.hpp"
#include "simplegl/Window.hpp"

#include "simplegl/Texture.hpp"

// @formatter:off
GLfloat vertices[] = {
	//     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

GLuint indices[] = {
	0,  1,  2,  // Bottom side
	0,  2,  3,  // Bottom side
	4,  6,  5,  // Left side
	7,  9,  8,  // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14  // Facing side
};

GLfloat lightVertices[] = {
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};
// @formatter:on

int main() {
    auto window = Window(800, 800, "Learning OpenGL!");

    window.SetDepthTest(true);

    std::cout << "OpenGL version: " << SimpleGL::Version() << std::endl;

    auto shader = Shader("resources/shaders/default");
    MeshBuffer meshBuffer(vertices, indices, {
                              Layout(Layout::Type::Float, 3), Layout(Layout::Type::Float, 3),
                              Layout(Layout::Type::Float, 2), Layout(Layout::Type::Float, 3)
                          });

    auto lightShader = Shader("resources/shaders/light");
    MeshBuffer lightMeshBuffer(lightVertices, lightIndices, {Layout(Layout::Type::Float, 3)});

    auto lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    auto lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    auto lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    auto pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    auto pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);


    lightShader.Activate();
    lightShader.SetUniform("model", lightModel);
    lightShader.SetUniform("lightColor", lightColor);

    shader.Activate();
    shader.SetUniform("model", pyramidModel);
    shader.SetUniform("lightColor", lightColor);
    shader.SetUniform("lightPos", lightPos);

    Texture texture("resources/textures/brick.png");

    auto tex0 = shader.GetUniform<int>("tex0");
    tex0.Set(0);

    Camera camera(window);
    camera.position = glm::vec3(0.0f, 0.3f, 2.0f);

    SimpleController movement(camera);

    while (!window.ShouldClose()) {
        window.ClearBackground(0.07f, 0.13f, 0.17f);

        movement.Update();

        shader.Activate();
        shader.SetUniform("camPos", camera.position);
        camera.Matrix(shader);
        texture.Activate();
        meshBuffer.Draw();

        lightShader.Activate();
        camera.Matrix(lightShader);
        lightMeshBuffer.Draw();

        window.Render();
    }
    return 0;
}
