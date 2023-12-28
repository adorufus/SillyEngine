#pragma once
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

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
