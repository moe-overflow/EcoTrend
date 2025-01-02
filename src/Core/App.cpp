#include "App.hpp"
#include "../UI/Layer.hpp"
#include "../UI/PlotViewer.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../../vendor/stb/stb_image_write.h"
#include "../UI/FileManagerLayer.hpp"

App::App()
{
	Window::Window_Settings window_settings = { 1600, 900 };
	_window = std::make_unique<Window>(std::move(window_settings));
	_window->Init();

	_window->AddLayer(std::make_shared<Dockspace>());
    _window->AddLayer(std::make_shared<PlotViewer>());
    _window->AddLayer(std::make_shared<MenuBar>());
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
