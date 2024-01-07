#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Texture texture, Renderer &renderer) : m_renderer(renderer), m_texture(texture)
{
    this->vertices = vertices;
    this->indices = indices;

    setupMesh();
}

void Mesh::setupMesh()
{
    m_renderer.init();
}

void Mesh::draw(Shader &shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for (unsigned int i = 0; i < m_texture.getTextures().size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        string number;
        string name = m_texture.getTextures()[i].type;
        if (name == "texture_diffuse")
            number = to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = to_string(specularNr++);
        else if (name == "texture_normal")
            number = to_string(normalNr++);
        else if (name == "texture_height")
            number = to_string(heightNr++);

        // cout << "texture id: " << textures[i].id  << endl;

        // shader.setFloat(("material." + name + number).c_str(), i);
        glUniform1i(glGetUniformLocation(shader.ID, ("material." + name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, m_texture.getTextures()[i].id);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}