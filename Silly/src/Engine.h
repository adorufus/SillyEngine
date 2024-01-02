#pragma once
#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>

using namespace std;

class Engine
{
private:
    Window *m_Window;

    bool m_isRunning;
    double m_frameTime;

    void run();

    void input(float delta);
    void update(float delta);
    void render();

    void stop();
    void cleanUp();
    
public:
    Engine(Window* window, double frameRate);
    ~Engine();

    static int fps;
    void init();
    void start();
};