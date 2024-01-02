#pragma once
#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Experimental_vertices_model_loader
{
private:
    glm::vec3 mPosition;
    glm::vec3 mRotation;
    glm::vec3 mScale;
    unsigned int VAO, VBO;

public:
    Experimental_vertices_model_loader(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
    void init(float vert[], size_t vertSize);
    void update(Shader shader);
    void render();
    void cleanup();
};
