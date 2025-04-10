#include "Popup.hpp"

#include <imgui.h>
#include <imgui_stdlib.h>
#include <filesystem>

using namespace ImGui;

void InsertJsonDirPopup::OnRender()
{
    if (Button("Insert JSON directory"))
    {
        OpenPopup("Select Item Popup");
    }

    if (BeginPopup("Select Item Popup"))
    {
        Text("Insert directory including JSON files");

        bool is_valid_directory = std::filesystem::is_directory(_inserted_file_name);

        if (!is_valid_directory)
        {
            // Change color for invalid directory (red background and text)
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));    // Text color (red)
            //ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));  // Border color (red)
            //ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.3f, 0.0f, 0.0f, 1.0f)); // Background color (dark red)
            //ImGui::PushStyleColor(
            //        ImGuiCol_FrameBgHovered,
            //        ImVec4(0.4f, 0.0f, 0.0f, 1.0f)
            //); // Hovered background (lighter red)
            //ImGui::PushStyleColor(
            //        ImGuiCol_FrameBgActive,
            //        ImVec4(0.4f, 0.0f, 0.0f, 1.0f)
            //); // Active background (lighter red)
        }

        InputText("Insert file name", &_inserted_file_name);
        
        // Revert to default colors after rendering the input field
        if (!is_valid_directory)
        {
            ImGui::PopStyleColor(1); // Pop 5 colors (we pushed 5 for text, border, and background)
        }
        
        
        if (Button("Select"))
        {
            if (is_valid_directory)
                CloseCurrentPopup();
        }
        EndPopup();
    }
}
