#include <stdexcept>
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

    glfwMakeContextCurrent(_glfw_window);

    // Enable vsync
    glfwSwapInterval(true);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc> (glfwGetProcAddress)); // todo: exception handling
}

void Window::Init_ImGUI()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); // (void)io;

    io.ConfigFlags |=
        ImGuiConfigFlags_DockingEnable |
        ImGuiConfigFlags_NavEnableKeyboard |
        ImGuiConfigFlags_ViewportsEnable;

    // todo: StyleColorDark

    const auto glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui_ImplGlfw_InitForOpenGL(_glfw_window, true);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glEnable(GL_DEPTH_TEST);

    // todo: fonts
}

void Window::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    /**/

    for (auto& layer : _layer_stack)
    {
        layer->OnRender();
    }

    ImGui::Render();

    int width, height;
    glfwGetFramebufferSize(_glfw_window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if(_save_chart)
    {
        GLuint fbo;
        GLuint texture = 0;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        {
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            std::vector<unsigned char> pixels(width * height * 4);
            glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

            stbi_flip_vertically_on_write(1); // Flip vertically
            stbi_write_png("plot.png", width, height, 4, pixels.data(), width * 4);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteFramebuffers(1, &fbo);

        _save_chart = false;
    }

    glfwSwapBuffers(_glfw_window);

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
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
