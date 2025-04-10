#pragma once

#include <string>
#include <imgui.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

struct WindowSettings
{
    int Width{ 1600 }, Height{ 900 };
    std::string Title = "ECO_TRENDREPORTER";
    ImFont* GlobalFont{};
    float FontSize = 24;

    bool StartMaximized;
    bool LightMode;

    void UpdateSize(GLFWwindow* window)
    {
        glfwGetWindowSize(window, &Width, &Height);
    }
};
