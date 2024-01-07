#pragma once
#include <string>
#include <vector>

using namespace std;

struct s_Texture{
    unsigned int id;
    string type;
    string path;
};

class Texture
{
private:
    vector<s_Texture> m_textures;

public:
    Texture();
    vector<s_Texture> getTextures();
    void assignTexture(s_Texture texture);
    void init();
    void draw();

};

