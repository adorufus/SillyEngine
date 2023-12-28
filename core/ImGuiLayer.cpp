#include "ImGuiLayer.h"
#include <cassert>
// #include <GLFW/glfw3.h>
#include <Window.h>

Window *mWindow = NULL;

ImGuiLayer::ImGuiLayer()
{
}

void ImGuiLayer::init(Window *window)
{

    // assert (mWindow == nullptr && "Window is null");
    mWindow = window;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    

    ImGuiIO &imGuiIo = ImGui::GetIO();
    (void)imGuiIo;

    imGuiIo.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    imGuiIo.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    imGuiIo.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    imGuiIo.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);

    ImGui_ImplOpenGL3_Init();
}

void ImGuiLayer::update(float deltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // bool showDemo = false;

    // ImGui::Begin("Scene", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    // auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
    // auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
    // auto viewportOffset = ImGui::GetWindowPos();

    // ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

    // ImVec2 wSize = ImGui::GetWindowSize();

    // ImGui::Image(reinterpret_cast<void*>(mWindow->getFramebufferTexture()), ImVec2(viewportPanelSize.x, viewportPanelSize.y), ImVec2(0, 1), ImVec2(1, 0));

    // ImGui::End();

    ImGui::Begin("Debug console");
    ImGui::Text("delta Time: %f", deltaTime);
    ImGui::End();

    // ImGui::ShowDemoWindow(&showDemo);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO &imGuiIo = ImGui::GetIO();
    (void)imGuiIo;
    if (imGuiIo.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow *backupCurrentContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);
    }
}

void ImGuiLayer::destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

// ImVec2 getLargestSizeForViewport() {
//     ImVec2 windowSize = ImVec2();
//     ImGui::GetContentRegionAvail();
// }