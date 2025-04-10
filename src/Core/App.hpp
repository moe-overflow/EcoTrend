#pragma once

#include "Window.hpp"
#include "../Template/Template.hpp"

#include <memory>

class App
{
public:

    inline static std::string const SIKORA_TEMPLATE_FILE_NAME{ "sikora_template" };
    inline static std::string const CUSTOMER_TEMPLATE_FILE_NAME{ "customer_template" };

    inline static std::string const CUSTOMER_TEMPLATE_PATH{ std::string(TEMPLATE_PATH) + "/customer_template.json" };

    App();

    // App singleton
    static App& Instance()
    {
        static App instance;
        return instance;
    }

    ~App();

    void Run();

    WindowSettings ReadConfigSettings();

    [[nodiscard]] Window& GetWindow() const
    {
        return *_window;
    }

    [[nodiscard]] bool UsingSikoraTemplate() const
    {
        return _using_sikora_template;
    }

    [[nodiscard]] std::shared_ptr<Template> GetSikoraTemplate()
    {
        return _sikora_template;
    }
    
    [[nodiscard]] std::shared_ptr<Template> GetCustomerTemplate()
    {
        return _customer_template;
    }

    void SetUsingSikoraTemplate(bool using_sikora_template)
    {
        _using_sikora_template = using_sikora_template;
    }

    void OverrideCustomerTemplate()
    {
        _customer_template;
    }

private:
    std::unique_ptr<Window> _window;

    std::shared_ptr<Template> _sikora_template;

    std::shared_ptr<Template> _customer_template;

    bool _using_sikora_template{ true }; // todo: to json
};
