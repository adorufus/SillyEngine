// #include "core/Window.h"
// #include "core/Engine.h"

// void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
// {
//     // float xpos = static_cast<float>(xposIn);
//     // float ypos = static_cast<float>(yposIn);

//     // if (firstMouse)
//     // {
//     //     lastX = xpos;
//     //     lastY = ypos;
//     //     firstMouse = false;
//     // }

//     // float xoffset = xpos - lastX;
//     // float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

//     // lastX = xpos;
//     // lastY = ypos;

//     // camera.ProcessMouseMovement(xoffset, yoffset);

// }

// void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
// {
//     // camera.ProcessMouseScroll(static_cast<float>(yoffset));
// }

// int main()
// {
//     Window windowInstance(800, 600, "Silly Engine");
//     windowInstance.initialize();
//     // windowInstance.setMouseCallback(mouse_callback, scroll_callback);
//     Engine engine(&windowInstance, 60);

//     engine.start();

//     return 0;
// }

#include <iostream>
//#include "glad/glad.h"
//#include <GLFW/glfw3.h>
//#include "core/Shader.h"
// #include "core/ImageLoader.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
#include "Window.h"
#include "Input.h"
#include "components/Camera.h"
#include "Model.h"

using namespace std;

glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
// glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
// glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

Camera camera(camPos);
bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float mvSpeed = 1.5f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void processInput(GLFWwindow *window)
{

    Input input(window);

    if (input.getKeyPressed(KeyCode::esc))
    {
        glfwSetWindowShouldClose(window, true);
    }

    float camSpeed = mvSpeed * deltaTime;

    if (input.getKeyPressed(KeyCode::SHIFT))
    {
        mvSpeed = 3.5f;
    }
    else
    {
        mvSpeed = 1.5f;
    }

    if (input.getKeyPressed(KeyCode::W))
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (input.getKeyPressed(KeyCode::S))
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (input.getKeyPressed(KeyCode::A))
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (input.getKeyPressed(KeyCode::D))
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (input.getKeyPressed(KeyCode::Q))
    {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }

    if (input.getKeyPressed(KeyCode::E))
    {
        camera.ProcessKeyboard(UP, deltaTime);
    }
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

int main()
{

    Window windowInstance(800, 600, "Silly Engine");
    windowInstance.setMouseCallback(mouse_callback, scroll_callback);
    windowInstance.initialize();
    Input input(windowInstance.getWindow());

    GLFWwindow *window = windowInstance.getWindow();

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    // positions all containers
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};

    // compile shaders section

    // Shader ourShader("assets/shaders/basic.vs", "assets/shaders/basic.fs");
    Shader ourShader("assets/shaders/vertexShader.vs", "assets/shaders/fragmentShader.vs");
    Shader lightingShader("assets/shaders/lightingShader.vs", "assets/shaders/lightingShader.fs");
    Model firstModel("assets/models/backpack.obj");

    unsigned int lightCubeVAO, VBO;
    glGenVertexArrays(1, &lightCubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!windowInstance.shouldClose())
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input proses
        processInput(window);

        // rendering proses
        windowInstance.clear();

        ourShader.use();

        ourShader.setVec3("light.position", -0.2f, -1.0f, -0.3f);
        ourShader.setVec3("viewPos", camera.Position);

        // light properties
        ourShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        ourShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        ourShader.setFloat("material.shininess", 32.0f);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        // glm::mat4 transform = glm::mat4(1.0f);

        projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
        view = camera.GetViewMatrix();

        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        ourShader.setMat4("model", model);
        firstModel.draw(ourShader);

        windowInstance.swapBuffers();
        windowInstance.poolEvents();
    }

    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
