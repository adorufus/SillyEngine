#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

#include <string>
#include <vector>

using namespace std;

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh
{
private:
    unsigned int VBO, EBO;
    void setupMesh();

public:
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    // ~Mesh();

    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;

    void draw(Shader &shader);
    
};


