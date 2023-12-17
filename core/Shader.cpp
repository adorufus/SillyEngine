#include "Shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath)
{
    string vertexCode;
    string fragmentCode;
    string geometryCode;
    ifstream vShaderFile;
    ifstream fShaderFile;
    ifstream gShaderFile;

    // ensure ifstream object can throw exceptions
    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    try
    {
        // Open the shader files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        stringstream vShaderStream, fShaderStream;

        // read the file buffer contents into stream
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // then close the file handlers
        vShaderFile.close();
        fShaderFile.close();

        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        if (geometryPath != nullptr)
        {
            gShaderFile.open(geometryPath);
            stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }

    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();

    cout << vShaderCode;

    unsigned int vertex, fragment, geometry;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
             << infoLog << endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
             << infoLog << endl;
    }

    if (geometryPath != nullptr)
    {
        const char *gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);

        if(!success) {
            glGetShaderInfoLog(geometry, 512, NULL, infoLog);
            cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n"
             << infoLog << endl;
        }

    }

    // Attach and link shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if(geometryPath != nullptr) glAttachShader(ID, geometry);
    glLinkProgram(ID);

    // check for errors
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n"
             << infoLog << endl;
    }

    // then delete because they already linked to our program and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(geometryPath != nullptr) glDeleteShader(geometry);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const string &name, const glm::mat4 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}