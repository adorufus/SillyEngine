#include "Window.h"
// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "experimental_vertices_model_loader.h"
#include "ScreenResUtil.h"
#include <cassert>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

GLFWwindow *Window::nWindow = NULL;
// void initialize_primitive();

float endTime = 0.0;
float deltaTime = 0.0f;
SillyEditor sillyEditor;

Window::Window(int width, int height, const char *title, Camera camera) : mFrambuffer(width, height), keyListener(camera)
{

    nWidth = width;
    nHeight = height;
    nTitle = title;

    

    currentScene = &sillyEditor;
}

void Window::initialize()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_OPENGL_CORE_PROFILE);

    createWindow();

    currentScene->init();
    currentScene->start();

    mImguiLayer.init(this);

    setupFramebuffer();

    // initialize_primitive();
}

void Window::createWindow()
{
    std::cout << "Device screen resolution: " << ScreenResUtil::getScreenRes().width << ":" << ScreenResUtil::getScreenRes().height << std::endl;
    nWidth = ScreenResUtil::getScreenRes().width;
    nHeight = ScreenResUtil::getScreenRes().height;
    nWindow = glfwCreateWindow(1280, 800, "Silly Engine", NULL, NULL);

    if (nWindow == NULL)
    {
        cout << "Failed to create window" << endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(nWindow);

    glfwSetFramebufferSizeCallback(nWindow, framebuffer_size_callback);

    glfwSetCursorPosCallback(nWindow, nMouseCallback);
    glfwSetScrollCallback(nWindow, nMouseScrollCallback);

    // glfwSetInputMode(nWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoaderLoadGL())
    {
        cout << "Failed to initialize GLAD" << endl;
    }

    stbi_set_flip_vertically_on_load(true); //<- enable to flip the texture

    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_STENCIL_TEST);
    // glDepthFunc(GL_ALWAYS);
    // glStencilMask(0xFF);
    // glStencilMask(0x00);
    // glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

int Window::getScreenWidth() {
    return nWidth;
}

int Window::getScreenHeight() {
    return nHeight;
}

Framebuffer Window::getFramebuffer()
{
    return mFrambuffer;
}

unsigned int Window::getFramebufferTexture()
{
    return mFrambuffer.getTextureId();
}

void Window::setupFramebuffer()
{
    mFrambuffer.init();
}

void Window::bindFramebuffer()
{
    mFrambuffer.bind();
}

void Window::unbindFramebuffer()
{
    mFrambuffer.unbind();
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

void Window::run()
{
    // initialize();
    update();

    this->destroy();
}

void Window::update()
{

    while (!shouldClose())
    {
        float beginTime = glfwGetTime();
        deltaTime = beginTime - endTime;
        endTime = beginTime;

        poolEvents();
        keyListener.process_input(this);

        mFrambuffer.bind();

        // std::cout << "Delta Time: " << deltaTime << std::endl;

        /// TODO: add scene renderer here

        if (deltaTime > 0.0f)
        {
            sillyEditor.update(deltaTime);
        }

        /// ENDTODO

        clear();

        mFrambuffer.unbind();

        glClear(GL_COLOR_BUFFER_BIT);

        mImguiLayer.update(deltaTime);

        swapBuffers();

        deltaTime = endTime - beginTime;
        beginTime = endTime;
        keyListener.setDeltaTime(deltaTime);
    }
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
    mImguiLayer.destroy();
    mFrambuffer.deleteFramebuffer();
    glfwDestroyWindow(nWindow);
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, height, width);
}
