#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H
#define STB_IMAGE_IMPLEMENTATION
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "stb_image.h"
#include <iostream>

using namespace std;

class TextureLoader
{
public:
    TextureLoader();
    void loadTexture(const char *path);
    unsigned int getTexture();

private:
    int nWidth, nHeight, nrChannels;
    unsigned int texture;
};

TextureLoader::TextureLoader()
{
   
}



void TextureLoader::loadTexture(const char *path)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(path, &nWidth, &nHeight, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture" << endl;
    }

    stbi_image_free(data);
}

unsigned int TextureLoader::getTexture()
{
    return texture;
}

#endif