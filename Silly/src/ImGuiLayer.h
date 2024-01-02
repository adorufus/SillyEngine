#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class Window;

class ImGuiLayer
{
private:
public:
    ImGuiLayer();
    void init(Window *window);
    void update(float deltaTime);
    void destroy();
};
