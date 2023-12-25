#include "ImageLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureLoader::TextureLoader()
{
}

void TextureLoader::loadTexture(const char *path, const string &directory, bool gamma)
{

    cout << "loading textures" << endl;
    string filename = string(path);
    filename = directory + '/' + filename;

    cout << "kaki kuda:" << filename << endl;

    glGenTextures(1, &texture);

    unsigned char *data = stbi_load(filename.c_str(), &nWidth, &nHeight, &nrChannels, 0);

    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        else 
            format = GL_RGB;

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, nWidth, nHeight, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        cout << "Failed to load texture" << endl;
        stbi_image_free(data);
    }
}

unsigned int TextureLoader::getTexture()
{
    return texture;
}