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
    
    ImGuiStyle &style = ImGui::GetStyle();
    if (imGuiIo.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);

    ImGui_ImplOpenGL3_Init();
}

void ImGuiLayer::setupDockingSpace() {
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking;

#ifdef __WINDOWS__
    windowFlags |= ImGuiWindowFlags_MenuBar;
#endif
    
    if(opt_fullscreen) {
        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }
    
    if(dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) {
        windowFlags |= ImGuiWindowFlags_NoBackground;
    }
    
    bool showWindow = true;
    
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    
    ImGui::Begin("Silly Editor", &showWindow, windowFlags);
    
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    else
    {
//        ShowDockingDisabledMessage();
    }
    
}

void ImGuiLayer::update(float deltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    bool showDemo = false;
    
    ImGuiIO &imGuiIo = ImGui::GetIO();
    (void)imGuiIo;
    
//    imGuiIo.DisplaySize.x = mWindow->getScreenWidth();
//    imGuiIo.DisplaySize.y = mWindow->getScreenHeight();
//    imGuiIo.DisplayFramebufferScale.x = 1.0f;
//    imGuiIo.DisplayFramebufferScale.y = 1.0f;
//    
//    int imguiCursor = ImGui::GetMouseCursor();
////    glfwSetCursor(mWindow->getWindow(), mouseCursors)
//    glfwSetInputMode(mWindow->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    setupDockingSpace();

        ImGui::ShowDemoWindow(&showDemo);
    
        ImGui::Begin("Debug console");
        ImGui::Text("delta Time: %f", deltaTime);
        ImGui::End();
    
        ImGui::Begin("Workspace");
        ImGui::Text("This is workspace");
        ImGui::End();
     ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
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
