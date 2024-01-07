#pragma once

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>
// #include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Texture;

class Model
{
private:
    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<s_Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    Renderer m_renderer;

public:
    vector<Mesh> meshes;
    string directory;
    vector<s_Texture> textures_loaded;
    bool gammaCorrection;
    Model(char *path, bool gamma = false, Renderer renderer);
    // ~Model();
    void draw(Shader &shader);
};
