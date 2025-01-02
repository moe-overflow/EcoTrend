#include "FileManagerLayer.hpp"

#include <iostream>
#include <fstream>

#include "imgui.h"
#include "nlohmann/json.hpp"
#include "../Utility/Files.hpp"

namespace fs = std::filesystem;

namespace
{
	void OpenFileDialog()
	{

	}

	auto LoadJSON(const std::string& file_name)
	{
		std::ifstream file(file_name);
		nlohmann::json json_data;
		if (file.is_open())	{ file >> json_data; }
		else {	std::cerr << "Error: Failed to open file: " << file_name << std::endl; }
		return json_data;
	}

	void Display_JSON(const nlohmann::json& json_data)
	{
		for (auto& [key, value] : json_data.items())
		{
			if (value.is_string()) { ImGui::Text("%s: %s", key.c_str(), value.get<std::string>().c_str()); }
			else if (value.is_number()) { ImGui::Text("%s: %f", key.c_str(), value.get<double>()); }
			else if (value.is_boolean()) { ImGui::Text("%s: %s", key.c_str(), value.get<bool>() ? "true" : "false"); }
		}
	}

	void HandleDragAndDrop()
	{
		if (ImGui::BeginDragDropTarget())
		{
			const auto* payload = ImGui::AcceptDragDropPayload("file_path");

			if (payload != nullptr)
			{
				std::string dropped = *((std::string*)payload->Data);
				auto json_data = LoadJSON(dropped);

				Display_JSON(json_data);


			}

		}
	}



}

void FileManagerLayer::OnRender()
{
    // ImGui::Text("Current selected file: %s", _selected_file.c_str());
    _insert_dir_popup->OnRender();

    ImGui::Text("Current directory: %s", _current_folder.c_str());
    std::vector<std::string> files = Files::GetJsonFiles(_current_folder);

    if (ImGui::BeginListBox("Files:", ImVec2(-FLT_MIN, 300)))
    {
        for (const auto& file : files)
            if (ImGui::Selectable(file.c_str()))
                _selected_file = file;

        ImGui::EndListBox();
    }

    if (!_selected_file.empty())
    {
        ImGui::Text("Current selected file: %s", _selected_file.c_str());
        if (ImGui::Button("Use selected for data")) {  }
    }


}




