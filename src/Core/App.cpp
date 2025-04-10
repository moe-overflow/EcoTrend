#include "App.hpp"
#include "../UI/Layer/Layer.hpp"
#include "../UI/Layer/FileManagerLayer.hpp"
#include "../UI/Layer/TemplateDesigner.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

App::App() :
      _window{ std::make_unique<Window>(std::move(ReadConfigSettings())) },
      _sikora_template   { std::make_shared<Template>(std::string(TEMPLATE_PATH) + "/" + SIKORA_TEMPLATE_FILE_NAME + ".json") },
      _customer_template { std::make_shared<Template>(CUSTOMER_TEMPLATE_PATH) }
{
    _window->Init();

    _window->AddLayer<Dockspace>();
    _window->AddLayer<MenuBar>(_window->GetSettings());
    _window->AddLayer<PlotViewer>();
    _window->AddLayer<FileManagerLayer>();
    _window->AddLayer<TemplateDesigner>(_customer_template->Get());

}

App::~App() 
{
    _window->SaveSettings();
}

void App::Run()
{
    while (!_window->ShouldClose())
    {
        _window->HandleEvents();
        _window->Render();
    }
}

WindowSettings App::ReadConfigSettings()
{
    WindowSettings config{};

    nlohmann::json j = JSON_Handler::ReadJsonFile(std::string(TEMPLATE_PATH) + "/config.json");

    config.Width = j["Global"]["Width"];
    config.Height = j["Global"]["Height"];
    config.Title = j["Global"]["Title"];
    // config.GlobalFont = j["Global"]["Font"];
    config.FontSize = j["Global"]["FontSize"];
    config.StartMaximized = j["Global"]["StartMaximized"];
    config.LightMode = j["Global"]["LightMode"];

    return config;
}


