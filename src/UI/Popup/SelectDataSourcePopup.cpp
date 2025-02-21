#include "Popup.hpp"
#include "imgui.h"

void SelectDataSourcePopup::OnRender()
{
    if (ImGui::Button("Choose chart type"))
    {
        ImGui::OpenPopup("Select Item Popup");
    }

    if (ImGui::BeginPopup("Select Item Popup"))
    {

        ImGui::EndPopup();
    }
}
