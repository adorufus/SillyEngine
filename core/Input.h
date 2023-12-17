#ifndef INPUT_H

#include <GLFW/glfw3.h>

enum class KeyCode {
    W = GLFW_KEY_W,
    A = GLFW_KEY_A,
    S = GLFW_KEY_S,
    D = GLFW_KEY_D,
    G = GLFW_KEY_G,
    esc = GLFW_KEY_ESCAPE,
};

class Input
{
private:
    GLFWwindow *nWindow;
public:
    Input(GLFWwindow *window);
    ~Input();
    bool getKeyPressed(KeyCode key) const;
};


#endif