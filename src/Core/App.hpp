#pragma once

#include "Window.hpp"

#include <memory>

class App
{
public:

    static App& Instance() {
        static App instance; // Guaranteed to be created only once
        return instance;
    }


	~App() = default;

	void Run();

    // std::unique_ptr<const Window> GetWindow() const { return _window; }

    [[nodiscard]] Window& GetWindow() const { return *_window; }

private:

    App();

	std::unique_ptr<Window> _window;


};



