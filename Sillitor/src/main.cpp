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
#include "assets_directory.h"

using namespace std;

glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
// glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
// glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

Camera camera(camPos);
bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

// float deltaTime = 0.0f;
float lastFrame = 0.0f;


glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Window windowInstance(800, 600, "Silly Engine", camera);


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

    windowInstance.setMouseCallback(mouse_callback, scroll_callback);
    windowInstance.initialize();
    Input input(windowInstance.getWindow());

    // GLFWwindow *window = windowInstance.getWindow();

    float planeVertices[] = {
        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
        5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
        -5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

        5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
        5.0f, -0.5f, -5.0f, 2.0f, 2.0f};

    float quadVertices[] = {
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f};

    //Experimental_vertices_model_loader planePrimitive;

    // compile shaders section

    // Shader ourShader(SHADER_DIR "/shaders/basic.vs", SHADER_DIR "/shaders/basic.fs");
    Shader ourShader(SHADER_DIR "/shaders/vertexShader.vs", SHADER_DIR "/shaders/fragmentShader.vs");
    Shader lightingShader(SHADER_DIR "/shaders/lightingShader.vs", SHADER_DIR "/shaders/lightingShader.fs");
    Shader stencilShader(SHADER_DIR "/shaders/stencil.vs", SHADER_DIR "/shaders/stencil.fs");
    Shader framebufferShader(SHADER_DIR  "/shaders/screenFramebuffer.vs", SHADER_DIR "/shaders/screenFramebuffer.fs");
    Model firstModel(SHADER_DIR "/models/backpack.obj");

    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    framebufferShader.use();
    framebufferShader.setInt("screenTexture", 0);

    size_t vertSize = sizeof(planeVertices) / sizeof(planeVertices[0]);
    //planePrimitive.init(planeVertices, vertSize);

    windowInstance.run();

    // windowInstance.setupFramebuffer();

    // bool showDemo = true;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // while (!windowInstance.shouldClose())
    // {

    //     float currentFrame = glfwGetTime();
    //     deltaTime = currentFrame - lastFrame;
    //     lastFrame = currentFrame;

    //     // input proses
    //     processInput(window);

    //     // windowInstance.bindFramebuffer();
    //     // glEnable(GL_DEPTH_TEST);

    //     // rendering proses
    //     windowInstance.clear();

    //     ourShader.use();

    //     ourShader.setVec3("light.position", -0.2f, -1.0f, -0.3f);
    //     ourShader.setVec3("viewPos", camera.Position);

    //     // light properties
    //     ourShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    //     ourShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    //     ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    //     ourShader.setFloat("material.shininess", 32.0f);

    //     glm::mat4 model = glm::mat4(1.0f);
    //     glm::mat4 view = glm::mat4(1.0f);
    //     glm::mat4 projection = glm::mat4(1.0f);
    //     // glm::mat4 transform = glm::mat4(1.0f);

    //     projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
    //     view = camera.GetViewMatrix();

    //     ourShader.setMat4("projection", projection);
    //     ourShader.setMat4("view", view);

    //     model = glm::translate(model, glm::vec3(0.0f, 1.8f, 0.0f));
    //     model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    //     ourShader.setMat4("model", model);
    //     firstModel.draw(ourShader);

    //     // glDisable(GL_DEPTH_TEST);

    //     // glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    //     // glStencilMask(0x00);
    //     // glDisable(GL_DEPTH_TEST);
    //     // stencilShader.use();

    //     planePrimitive.update(ourShader);

    //     // windowInstance.unbindFramebuffer();
    //     // glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
    //     // clear all relevant buffers
    //     // glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
    //     // glClear(GL_COLOR_BUFFER_BIT);

    //     // framebufferShader.use();
    //     // glBindVertexArray(quadVAO);
    //     // glBindTexture(GL_TEXTURE_2D, windowInstance.getFramebufferTexture());
    //     // glDrawArrays(GL_TRIANGLES, 0, 6);

    //     // glStencilMask(0xFF);
    //     // glStencilFunc(GL_ALWAYS, 0, 0xFF);
    //     // glEnable(GL_DEPTH_TEST);

    //     windowInstance.update(deltaTime);
    // }

    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);

    //planePrimitive.cleanup();
    return 0;
}
