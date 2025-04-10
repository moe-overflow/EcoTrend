#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "../UI/Layer/Layer.hpp"

class Layer;

class Window
{
public:
    explicit Window(WindowSettings const& settings);

    Window(Window const&) = delete;
    Window(Window&&) = default;

    Window& operator=(Window const&) = delete;
    Window& operator=(Window&&) = default;

    ~Window();

    void Init();

    void Render();

    [[nodiscard]] bool ShouldClose() const;

    void HandleEvents();

    void Destroy() const;

    [[nodiscard]] std::pair<int, int> GetWindowPosition();

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

    [[nodiscard]] std::pair<double, double> GetMousePosition();

    void SaveSettings();

    [[nodiscard]] inline std::shared_ptr<WindowSettings> GetSettings()
    {
        return _settings;
    }

    template<typename T, typename... Args>
    T& AddLayer(Args&&... args)
    {
        static_assert(std::is_base_of<Layer, T>::value);
        auto layer = std::make_shared<T>(std::forward<Args>(args)...);
        T& ref = *layer;
        _layer_stack.emplace_back(layer);
        layer->OnAttach();
        return ref;
    }

private:
    std::shared_ptr<WindowSettings> _settings;

    GLFWwindow* _glfw_window;

    void Init_ImGUI();

    void Init_GLFW();

    static void AttachDockspace(bool* p_open);

    std::vector<std::shared_ptr<Layer>> _layer_stack;

    bool _light_mode;
};
