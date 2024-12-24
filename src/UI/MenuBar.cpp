#include "Layer.hpp"

#include "implot.h"
#include "../Core/App.hpp"

void MenuBar::OnRender()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open...")) {}
            if (ImGui::MenuItem("Close")) { App::Instance().GetWindow().Destroy(); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("View")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Help")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}


