#pragma once

#include "Window.hpp"

#include <memory>

class App
{
public:
	App();
	~App() = default;

	void Run();

private:
	std::unique_ptr<Window> _window;


};



