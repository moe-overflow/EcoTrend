#include <stdexcept>
#include <iostream>
#include "Window.hpp"

#include "implot.h"
#include "../../vendor/stb/stb_image_write.h"


Window::Window(const Window_Settings& settings) :
	_settings{ std::move(settings) },
	_glfw_window{ nullptr }
{}

Window::~Window()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    ImPlot::DestroyContext();

    if (_glfw_window) {
        glfwDestroyWindow(_glfw_window);
    }
    glfwTerminate();
}

void Window::Init()
{
	Init_GLFW();
    Init_ImGUI();
    ImPlot::CreateContext();
}

void Window::Init_GLFW()
{
    glfwInit(); // todo: exception handling

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    _glfw_window = glfwCreateWindow(_settings.Width, _settings.Height, _settings.Title.c_str(), nullptr, nullptr);

    if (!_glfw_window)
        glfwTerminate();

    int buffer_width, buffer_height;
    glfwGetFramebufferSize(_glfw_window, &buffer_width, &buffer_height);

    glfwMakeContextCurrent(_glfw_window);

    // Enable vsync
    glfwSwapInterval(true);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc> (glfwGetProcAddress)); // todo: exception handling

    glViewport(0, 0, buffer_width, buffer_height);
    BindFramebuffer(buffer_width, buffer_height);
}

void Window::Init_ImGUI() const
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |=
        ImGuiConfigFlags_DockingEnable |
        ImGuiConfigFlags_NavEnableKeyboard |
        ImGuiConfigFlags_ViewportsEnable;

    // todo: StyleColorDark

    const auto glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui_ImplGlfw_InitForOpenGL(_glfw_window, true);

    // todo: fonts
}

void Window::BindFramebuffer(int width, int height)
{
    GLuint frame_buffer;
    GLuint render_buffer;
    GLuint texture;

    glGenFramebuffers(1, &frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glGenRenderbuffers(1, &render_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, render_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, render_buffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "Error: Framebuffer incomplete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(_glfw_window);
}

void Window::AttachDockspace(bool* p_open) const
{
    static bool fullscreen = true;
    static bool padding = false;

    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode; 
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    
    if (fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= 
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | 
            ImGuiWindowFlags_NoMove | 
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus;
    }
    else 
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    if (!padding) 
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", p_open, window_flags);
    if (!padding) 
        ImGui::PopStyleVar();

    if (fullscreen)
        ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) 
    {
        ImGuiID dockspace_id = ImGui::GetID("DockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    ImGui::End();
}

void Window::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    bool doc = true;
    AttachDockspace(&doc);

    /**/

    for (auto& layer : _layer_stack)
    {
        layer->OnRender();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ImGui::Render();

    {
        int display_w, display_h;
        glfwGetFramebufferSize(_glfw_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_context);
        }
    }

    SwapBuffers();
    Handle_Events();

}

void Window::Handle_Events() const
{
    glfwPollEvents();
}

bool Window::Should_Close() const
{
    return glfwWindowShouldClose(_glfw_window);
}

void Window::Destroy() const
{
    glfwSetWindowShouldClose(_glfw_window, true);
}

void Window::AddLayer(const std::shared_ptr<Layer>& layer)
{
    _layer_stack.emplace_back(layer);
}

void Window::SaveChart()
{
    _save_chart = true;
}
