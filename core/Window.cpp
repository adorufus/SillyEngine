#include "Window.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

GLFWwindow *Window::nWindow = NULL;

Window::Window(int width, int height, const char *title)
{

    nWidth = width;
    nHeight = height;
    nTitle = title;
}

Window::~Window()
{
    destroy();
}

void Window::initialize()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_OPENGL_CORE_PROFILE);

    createWindow();
}

void Window::createWindow()
{
    nWindow = glfwCreateWindow(800, 600, "Silly Engine", NULL, NULL);

    if (nWindow == NULL)
    {
        cout << "Failed to create window" << endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(nWindow);

    glfwSetFramebufferSizeCallback(nWindow, framebuffer_size_callback);

    glfwSetCursorPosCallback(nWindow, nMouseCallback);
    glfwSetScrollCallback(nWindow, nMouseScrollCallback);

    glfwSetInputMode(nWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
    }

    glEnable(GL_DEPTH_TEST);
}

GLFWwindow *Window::getWindow()
{
    return nWindow;
}

void Window::setMouseCallback(GLFWcursorposfun mouse_callback, GLFWscrollfun scroll_callback)
{
    nMouseCallback = mouse_callback;
    nMouseScrollCallback = scroll_callback;
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(nWindow);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(nWindow);
}

void Window::poolEvents()
{
    glfwPollEvents();
}

void Window::clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::destroy()
{
    glfwDestroyWindow(nWindow);
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, height, width);
}