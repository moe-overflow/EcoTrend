#include "FileManagerLayer.hpp"

#include <imgui.h>
#include <iostream>

#include "../Core/App.hpp"
#include "../Utility/Files.hpp"

void FileManagerLayer::OnRender()
{
    ImGui::Begin("File Manager");

    // ImGui::Text("Current selected file: %s", _selected_file.c_str());
    _insert_dir_popup->OnRender();

    ImGui::Text("Current directory: %s", _current_folder.c_str());
    std::vector<std::string> files = Files::GetJsonFiles(_current_folder);

    if (ImGui::BeginListBox("Files:", ImVec2(-FLT_MIN, 300)))
    {
        for (auto const& file : files)
            if (ImGui::Selectable(file.c_str()))
                _selected_file = file;

        ImGui::EndListBox();
    }

    if (!_selected_file.empty())
    {
        ImGui::Text("Current selected file: %s", _selected_file.c_str());
        if (ImGui::Button("Use selected for data"))
        {
            // read content of json file and assign read data to current plot data (PlotViewer)
            auto json_content = JSON_Handler::ReadJsonFile(_selected_file);
            App::Instance().GetWindow().GetLayer<PlotViewer>(LayerType::PlotViewer)->SetPlotData(json_content);
        }
    }

    ImGui::End();
}
