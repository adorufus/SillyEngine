#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "core/Shader.h"
#include "core/ImageLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/Input.h"
#include "core/Window.h"

using namespace std;

glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

void processInput(GLFWwindow *window)
{

    Input input(window);

    if (input.getKeyPressed(KeyCode::esc))
    {
        glfwSetWindowShouldClose(window, true);
    }

    const float camSpeed = 0.05f;
    if (input.getKeyPressed(KeyCode::W))
    {
        camPos += camSpeed * camFront;
    }
    if (input.getKeyPressed(KeyCode::S))
    {
        camPos -= camSpeed * camFront;
    }

    if (input.getKeyPressed(KeyCode::A))
    {
        camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
    }

    if (input.getKeyPressed(KeyCode::D))
    {
        camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
    }
}

int main()
{

    Window windowInstance(800, 600, "Silly Engine");
    Window windowInstance2(800, 600, "Silly Engine Window 2");
    windowInstance.initialize();
    Input input(windowInstance.getWindow());

    GLFWwindow *window = windowInstance.getWindow();
    GLFWwindow *window2 = nullptr;

    if (input.getKeyPressed(KeyCode::G))
    {
        windowInstance2.initialize();

        window2 = windowInstance2.getWindow();
    }

    // compile shaders section

    Shader ourShader("assets/shaders/vertexShader.vs", "assets/shaders/fragmentShader.vs");

    // Create shader program

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // linking vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);

    // Unbind the buffer
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Unbind the Vertex Array
    // glBindVertexArray(0);

    // end of shader section

    // Load an ImageTexture

    // TextureLoader textureLoader;
    // textureLoader.loadTexture("assets/images/container.jpg");
    TextureLoader textureLoader2;
    textureLoader2.loadTexture("assets/images/image2.png");

    ourShader.use();
    // glUniform1i(glGetUniformLocation(ourShader.ID, "sTexture2"), 0);
    // ourShader.setInt("sTexture", 0);
    ourShader.setInt("sTexture2", 1);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!windowInstance.shouldClose())
    {
        // input proses
        processInput(window);

        // rendering proses
        windowInstance.clear();

        // bind all textures
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, textureLoader.getTexture());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureLoader2.getTexture());

        // Using the shader program
        ourShader.use();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        // float radius = 10.0f;
        // float camX = static_cast<float>(sin(glfwGetTime()) * radius);
        // float camZ = static_cast<float>(cos(glfwGetTime()) * radius);

        model = glm::rotate(model, 20.0f, glm::vec3(1.0f, 0.3f, 0.5f));

        view = glm::lookAt(camPos, camPos + camFront, camUp);
        ourShader.setMat4("view", view);

        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        // unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        ourShader.setMat4("projection", projection);

        // glUniform4f(vertexColorLocation, greenValue, 0.0f, 0.0f, 1.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        windowInstance.swapBuffers();
        windowInstance.poolEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // glfwTerminate();
    return 0;
}