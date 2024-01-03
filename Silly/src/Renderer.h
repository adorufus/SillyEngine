//
// Created by Oktaviano on 02/01/24.
//

#pragma once
//#include <GLFW/glfw3.h>
#include "Window.h"
#include "Camera.h"


class Renderer {
private:
    Camera *m_mainCamera;

public:
    Renderer();
    void init();

    void render();

    inline Camera& getMainCamera() {return *m_mainCamera;}
    inline void add(Camera *camera) {m_mainCamera = camera;}

    void destroy();
};
