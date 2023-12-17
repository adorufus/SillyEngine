#ifndef SHADER_H

#include <glad/glad.h>
#include "glm/glm.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {
public:
    unsigned int ID;

    //constructor for reading and build the shaders
    Shader(const char* vertexPath, const char*  fragmentPath, const char *geometryPath = nullptr);

    void use();
    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;
    void setMat4(const string &name, const glm::mat4 &value) const;


};

#endif