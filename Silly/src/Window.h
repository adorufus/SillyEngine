#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

class Window
{
private:
    static GLFWwindow *nWindow;
    int nWidth, nHeight;
    const char *nTitle;
    GLFWcursorposfun nMouseCallback;
    GLFWscrollfun nMouseScrollCallback;

public:
    Window(int width, int height, const char *title);
    ~Window();
    void initialize();
    void createWindow();
    static GLFWwindow *getWindow();
    bool shouldClose();
    void swapBuffers();
    void poolEvents();
    static void clear();
    void destroy();
    void setMouseCallback(GLFWcursorposfun mouse_callback, GLFWscrollfun scroll_callback);
};
