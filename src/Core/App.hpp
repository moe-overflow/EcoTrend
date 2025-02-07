#pragma once

#include "Window.hpp"

#include <memory>

class App
{
public:
	App();

	static App& Instance() 
	{
		static App instance;
		return instance;
	}

	~App() = default;

	void Run();

	[[nodiscard]] Window& GetWindow() const { return *_window; }

private:
	std::unique_ptr<Window> _window;


};



