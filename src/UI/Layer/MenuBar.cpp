#include "Layer.hpp"

#include "imgui.h"
#include "../../Core/App.hpp"
#include "../../Utility/JsonHandler.hpp"

using json = nlohmann::json;

using namespace ImGui;

void MenuBar::OnAttach()
{
    _start_maximized_toggle = _window_settings->StartMaximized;
    _light_mode = _window_settings->LightMode;
}

void MenuBar::OnRender()
{
    if (BeginMainMenuBar())
    {
        if (BeginMenu("File"))
        {
            if (MenuItem("Open"))
            {

            }
            if (MenuItem("Close"))
            {
                App::Instance().GetWindow().Destroy();
            }
            EndMenu();
        }
        if (BeginMenu("View"))
        {

            if (MenuItem("Enable Starting Window Maximized", nullptr, &_start_maximized_toggle))
            {
                std::cout << _start_maximized_toggle << std::endl;
                _window_settings->StartMaximized = _start_maximized_toggle;
            }

            if (MenuItem("Light Mode", nullptr, &_light_mode))
            {
                _window_settings->LightMode = _light_mode;
            }


            EndMenu();
        }
        if (BeginMenu("Help"))
        {
            if (MenuItem("Help"))
            {
            }
#ifndef NDEBUG
            if (MenuItem("Demo", nullptr, &_enable_imgui_demo_view))
            {
            }
#endif
            EndMenu();
        }
        EndMainMenuBar();
    }

    if (_enable_imgui_demo_view)
        ShowDemoWindow(&_enable_imgui_demo_view);

}
