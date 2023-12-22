#pragma once

// #define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
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

class Model
{
private:
    vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded;
    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

public:
    Model(char *path);
    // ~Model();
    void draw(Shader &shader);
};
