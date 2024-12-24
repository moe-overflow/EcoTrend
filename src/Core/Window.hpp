#include <string>
#include <vector>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Layer;

class Window
{
public:

	struct Window_Settings
	{
		unsigned int Width, Height;
		std::string Title = "EcoTrend";
	};

	explicit Window(const Window_Settings& settings);

	Window(const Window&) = delete;
	Window(Window&&) = default;

	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = default;


	~Window();

	void Init();

	void Render();
	
	[[nodiscard]] bool Should_Close() const;

	void Handle_Events() const;
	
	void Destroy() const;

	void AddLayer(const std::shared_ptr<Layer>& layer);



private:
	Window_Settings _settings;

	GLFWwindow* _glfw_window;

	void Init_ImGUI();

	void Init_GLFW();

	std::vector<std::shared_ptr<Layer>> _layer_stack;

};

