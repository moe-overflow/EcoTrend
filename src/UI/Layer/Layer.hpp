#pragma once

#include <memory>
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
    virtual void OnRender() override;

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

    MenuBar(std::shared_ptr<WindowSettings> settings) : 
        _window_settings{ settings }
    { } 

    virtual void OnRender() override;

    virtual void OnAttach() override;

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


