#include "App.hpp"
#include "../UI/FileManagerLayer.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

App::App()
{
    Window::Window_Settings window_settings = { 1600, 900 };
    _window = std::make_unique<Window>(std::move(window_settings));
    _window->Init();

    _window->AddLayer(std::make_shared<Dockspace>());
    _window->AddLayer(std::make_shared<MenuBar>());
    _window->AddLayer(std::make_shared<PlotViewer>());
    _window->AddLayer(std::make_shared<FileManagerLayer>());
}

void App::Run()
{
    while (!_window->Should_Close())
    {
        _window->Handle_Events();
        _window->Render();
    }
}
