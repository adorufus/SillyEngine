#include "Input.h"

Input::Input(GLFWwindow *window) : nWindow(window)
{
    
}

bool Input::getKeyPressed(KeyCode key) const
{
    return glfwGetKey(nWindow, static_cast<int>(key)) == GLFW_PRESS;
}

void Input::update(float delta) {
    glfwPollEvents();
}

Input::~Input()
{
}