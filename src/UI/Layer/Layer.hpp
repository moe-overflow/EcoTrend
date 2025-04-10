#pragma once

#include <memory>
#include <utility>
#include "../../Core/WindowSettings.hpp"

enum class LayerType
{
    Dockspace,
    PlotViewer,
    MenuBar,
    FileManagerLayer,
    TemplateDesigner,

    Popup

};

class Layer
{
public:
    virtual ~Layer() = default;

    virtual void OnRender(){};

    virtual void OnUpdate(){};

    virtual void OnAttach(){};
    // virtual void OnDetach() {};

    [[nodiscard]] virtual LayerType GetType() const = 0;
};

class Dockspace : public Layer
{
public:
    void OnRender() override;

    [[nodiscard]] LayerType GetType() const override
    {
        return LayerType::Dockspace;
    }

private:
    bool _full_screen = true;
};

class MenuBar : public Layer
{
public:

    explicit MenuBar(std::shared_ptr<WindowSettings> settings) :
        _window_settings{std::move( settings )}
    { } 

    void OnRender() override;

    void OnAttach() override;

    [[nodiscard]] LayerType GetType() const override
    {
        return LayerType::MenuBar;
    }

private:
    std::shared_ptr<WindowSettings> _window_settings;

    bool _start_maximized_toggle{ false };
    bool _light_mode{};

    bool _enable_imgui_demo_view{ false };

};


