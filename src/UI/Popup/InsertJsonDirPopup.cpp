#include "Popup.hpp"
#include "imgui.h"

void InsertJsonDirPopup::OnRender()
{
    if (ImGui::Button("Insert JSON directory"))
    {
        ImGui::OpenPopup("Select Item Popup");
    }

    if (ImGui::BeginPopup("Select Item Popup"))
    {
        if (ImGui::InputText("Insert file name", const_cast<char*>(_inserted_file_name.c_str()), 50))
        {

        }
        ImGui::EndPopup();
    }
}