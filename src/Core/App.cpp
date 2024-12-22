#include "App.hpp"
#include "../UI/Layer.hpp"
#include "../UI/PlotViewer.hpp"

App::App()
{
	Window::Window_Settings window_settings = { 1600, 900 };
	_window = std::make_unique<Window>(std::move(window_settings));
	_window->Init();

	// _window->AddLayer(std::make_shared<FileManagerLayer>());
	_window->AddLayer(std::make_shared<Dockspace>());
    _window->AddLayer(std::make_shared<PlotViewer>());
}

void App::Run()
{
	while (!_window->Should_Close())
	{
		_window->Handle_Events();
		_window->Render();
	}
}
