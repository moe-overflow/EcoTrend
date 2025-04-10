#include "Window.hpp"

#include "../UI/Layer/Layer.hpp"
#include "../Utility/JsonHandler.hpp"
#include "implot.h"

using json = nlohmann::json;

Window::Window(WindowSettings const& settings)
    : _settings{ std::make_shared<WindowSettings>(settings) },
      _glfw_window{ nullptr }
{
}

Window::~Window()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();
    ImPlot::DestroyContext();

    if (_glfw_window)
    {
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

    _glfw_window = glfwCreateWindow(_settings->Width, _settings->Height, _settings->Title.c_str(), nullptr, nullptr);

    if (!_glfw_window)
        glfwTerminate();

    int buffer_width, buffer_height;
    glfwGetFramebufferSize(_glfw_window, &buffer_width, &buffer_height);

    glfwMakeContextCurrent(_glfw_window);


    if (_settings->StartMaximized)
        glfwMaximizeWindow(_glfw_window);

    // glfwWindow

    // Enable vsync
    glfwSwapInterval(true);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); // todo: exception handling

    glViewport(0, 0, buffer_width, buffer_height);
    BindFramebuffer(buffer_width, buffer_height);
}

void Window::Init_ImGUI()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |=
            ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_ViewportsEnable;

    // Setting up font
    {
        io.Fonts->Clear();

        io.Fonts->AddFontDefault();
        auto font_file = ASSETS_PATH "/fonts/FUTURAL.ttf";

        _settings->GlobalFont = io.Fonts->AddFontFromFileTTF(
                font_file,
                _settings->FontSize,
                nullptr,
                io.Fonts->GetGlyphRangesJapanese()
        );

        io.Fonts->Build();
    }

    auto const glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui_ImplGlfw_InitForOpenGL(_glfw_window, true);


    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glEnable(GL_DEPTH_TEST);
}

void Window::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    _settings->LightMode ? ImGui::StyleColorsLight() : ImGui::StyleColorsDark();

    bool doc = true;

    ImGui::PushFont(_settings->GlobalFont);

    AttachDockspace(&doc);

    /**/

    for (auto& layer : _layer_stack)
    {
        layer->OnRender();
    }

    ImGui::PopFont();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ImGui::Render();

    {
        int display_width, display_height;
        glfwGetFramebufferSize(_glfw_window, &display_width, &display_height);
        glViewport(0, 0, display_width, display_height);
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
    HandleEvents();
}


void Window::AttachDockspace(bool* p_open)
{
    static bool fullscreen = true;
    static bool padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    if (fullscreen)
    {
        ImGuiViewport const* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
                        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus
                        | ImGuiWindowFlags_NoNavFocus;
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

void Window::SwapBuffers() const
{
    glfwSwapBuffers(_glfw_window);
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
    glEnable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

std::pair<double, double> Window::GetMousePosition()
{
    double x, y;
    glfwGetCursorPos(_glfw_window, &x, &y);
    return std::pair{ x, y };
}

void Window::HandleEvents()
{
    glfwPollEvents();
    _settings->UpdateSize(_glfw_window);
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(_glfw_window);
}

void Window::Destroy() const
{
    glfwSetWindowShouldClose(_glfw_window, true);
}

std::pair<int, int> Window::GetWindowPosition()
{
    int x, y;
    glfwGetWindowPos(_glfw_window, &x, &y);
    return { x, y };
}

void Window::SaveSettings()
{
    std::string const path = std::string(TEMPLATE_PATH) + "/config.json";
    nlohmann::json j = JSON_Handler::ReadJsonFile(path);

    j["Global"]["Width"] = _settings->Width;
    j["Global"]["Height"] = _settings->Height;
    j["Global"]["Title"] = _settings->Title;
    j["Global"]["FontSize"] = _settings->FontSize;

    j["Global"]["StartMaximized"] = _settings->StartMaximized;
    j["Global"]["LightMode"] = _settings->LightMode;

    JSON_Handler::WriteJsonFile(j, path);
}
