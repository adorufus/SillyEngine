//
// Created by Oktaviano on 02/01/24.
//

#pragma once
//#include <GLFW/glfw3.h>
#include <vector>
#include "Window.h"
#include "Camera.h"
#include "Shader.h"


class Renderer {
private:
    unsigned int VAO, VBO, EBO;
    Camera *m_mainCamera;
    Shader m_shader;

public:
    Renderer(Shader shader);
    void init();

    void render();

    inline Camera& getMainCamera() {return *m_mainCamera;}
    inline void add(Camera *camera) {m_mainCamera = camera;}

    void destroy();
};
