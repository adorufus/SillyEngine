#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

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

class Mesh
{
private:
    
    void setupMesh();
    Renderer m_renderer;
    Texture m_texture;
    vector<Vertex> vertices;
    vector<unsigned int> indices;

public:
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Texture texture, Renderer &renderer);
    // ~Mesh();
    void draw(Shader &shader);
    
};


