#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Framebuffer.h"
#include "ImGuiLayer.h"
#include "KeyListener.h"
#include "components/Camera.h"
#include "Scene.h"
#include "SillyEditor.h"

using namespace std;



class Window
{
private:
    static GLFWwindow *nWindow;
    int nWidth, nHeight;
    const char *nTitle;
    GLFWcursorposfun nMouseCallback;
    GLFWscrollfun nMouseScrollCallback;
    Framebuffer mFrambuffer;
    ImGuiLayer mImguiLayer;
    KeyListener keyListener;
    Scene *currentScene;

public:
    Window(int width, int height, const char *title, Camera camera);
    void initialize();
    void createWindow();
    void run();
    static GLFWwindow *getWindow();
    void update();
    bool shouldClose();
    void swapBuffers();
    void poolEvents();
    void setupFramebuffer();
    void bindFramebuffer();
    void unbindFramebuffer();
    static void clear();
    void destroy();
    unsigned int getFramebufferTexture();
    Framebuffer getFramebuffer();
    void setMouseCallback(GLFWcursorposfun mouse_callback, GLFWscrollfun scroll_callback);
};
