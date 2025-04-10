#include "Popup.hpp"
#include "imgui.h"

void SaveChartPopup::OnRender()
{
    if (ImGui::Button("Save chart..."))
    {
        // App::Instance().GetWindow().SaveChart();
    }
}
