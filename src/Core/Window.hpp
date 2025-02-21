#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "../UI/Layer.hpp"

class Layer;

class Window
{
public:
    struct Window_Settings
    {
        unsigned int Width, Height;
        std::string Title = "EcoTrend";
    };

    explicit Window(Window_Settings const& settings);

    Window(Window const&) = delete;
    Window(Window&&) = default;

    Window& operator=(Window const&) = delete;
    Window& operator=(Window&&) = default;

    ~Window();

    void Init();

    void Render();

    [[nodiscard]] bool Should_Close() const;

    void Handle_Events() const;

    void Destroy() const;

    void AddLayer(std::shared_ptr<Layer> layer);

    std::pair<int, int> GetWindowPosition();

    template<typename T>
    [[nodiscard]] std::shared_ptr<T> GetLayer(LayerType type)
    {
        auto it = std::find_if(
                _layer_stack.begin(),
                _layer_stack.end(),
                [type](std::shared_ptr<Layer> const& layer) { return layer->GetType() == type; }
        );

        if (it != _layer_stack.end())
            return std::dynamic_pointer_cast<T>(*it);

        throw std::runtime_error("Layer not found");
    }

    void SwapBuffers() const;

    static void BindFramebuffer(int width, int height);

    std::pair<double, double> GetMousePosition();

private:
    Window_Settings _settings;

    GLFWwindow* _glfw_window;

    void Init_ImGUI();

    void Init_GLFW();

    static void AttachDockspace(bool* p_open);

    std::vector<std::shared_ptr<Layer>> _layer_stack;
};
