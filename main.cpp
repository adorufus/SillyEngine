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
#include "core/components/Camera.h"

using namespace std;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
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

    // compile shaders section

    Shader ourShader("assets/shaders/vertexShader.vs", "assets/shaders/fragmentShader.vs");
    Shader lightingShader("assets/shaders/lightingShader.vs", "assets/shaders/lightingShader.fs");

    // Create shader program

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    float vertices[] = {
        -0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,

        -0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,

        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,

        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,

        -0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        -0.5f,

        -0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        -0.5f,
    };

    unsigned int VAO, VBO;
    unsigned int lightVAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // linking vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);

    // linking light vertex attribute
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

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

    // ourShader.use();
    // glUniform1i(glGetUniformLocation(ourShader.ID, "sTexture2"), 0);
    // ourShader.setInt("sTexture", 0);
    // ourShader.setInt("sTexture2", 1);

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

        // bind all textures
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, textureLoader.getTexture());
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, textureLoader2.getTexture());

        ourShader.use();
        ourShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        // glm::mat4 transform = glm::mat4(1.0f);

        projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
        view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Using the shader program

        lightingShader.use();
        lightingShader.setMat4("view", view);

        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        model = glm::rotate(model, 20.0f, glm::vec3(1.0f, 0.3f, 0.5f));

        lightingShader.setMat4("model", model);

        // glUniform4f(vertexColorLocation, greenValue, 0.0f, 0.0f, 1.0f);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        windowInstance.swapBuffers();
        windowInstance.poolEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // glfwTerminate();
    return 0;
}