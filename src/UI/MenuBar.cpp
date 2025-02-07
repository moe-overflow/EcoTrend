#include "Layer.hpp"

#include "implot.h"

void MenuBar::OnRender()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open...")) {}
            if (ImGui::MenuItem("Close")) { /* this->Destroy(); */ }
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
