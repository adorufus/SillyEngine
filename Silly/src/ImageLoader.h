#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

class TextureLoader
{
public:
    TextureLoader();
    void loadTexture(const char *path, const string &directory, bool gamma = false);
    unsigned int getTexture();

private:
    int nWidth, nHeight, nrChannels;
    unsigned int texture;
};
