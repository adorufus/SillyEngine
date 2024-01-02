#include "experimental_vertices_model_loader.h"


Experimental_vertices_model_loader::Experimental_vertices_model_loader(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : mPosition(position), mRotation(rotation), mScale(scale)
{
}

void Experimental_vertices_model_loader::init(float vert[], size_t vertSize)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float), vert, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);
}

void Experimental_vertices_model_loader::update(Shader shader)
{
    glBindVertexArray(VAO);
    // glBindTexture(GL_TEXTURE_2D, floorTexture);
    shader.setMat4("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Experimental_vertices_model_loader::render()
{
}

void Experimental_vertices_model_loader::cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}