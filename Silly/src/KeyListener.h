#pragma once
// #include <GLFW/glfw3.h>
#include "components/Camera.h"

class Window;

class KeyListener
{
private:
    float mDeltaTime;
    Camera mEditorCamera;
    
public:
    KeyListener(Camera camera);
    void process_input(Window *window);
    // static void process_input(GLFWwindow *window, float deltaTime);
    float getDeltaTime();
    void setDeltaTime(float deltaTime);
    Camera getCamera();
};
