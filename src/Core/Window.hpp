#include <string>
#include <vector>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../UI/Layer.hpp"

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

    template<typename T>
    std::shared_ptr<T> GetLayer(LayerType type)
    {
        auto it = std::find_if
        (
			_layer_stack.begin(), _layer_stack.end(),
			[type](const std::shared_ptr<Layer>& layer)
			{
				return layer->GetType() == type;
			}
        );

        if(it != _layer_stack.end()) return std::dynamic_pointer_cast<T>(*it);

        throw std::runtime_error("Layer not found");

    }

    void SaveChart();

	void BindFramebuffer(int width, int height);

	void SwapBuffers() const;

private:

    void Init_ImGUI() const;

    void Init_GLFW();

	void AttachDockspace(bool* p_open) const;


private:
	Window_Settings _settings;

	GLFWwindow* _glfw_window;

	std::vector<std::shared_ptr<Layer>> _layer_stack;

    bool _save_chart = false;
};

