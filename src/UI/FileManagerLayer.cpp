#include "FileManagerLayer.hpp"

#include "imgui.h"
#include <iostream>

#include <fstream>

#include "nlohmann/json.hpp"
#include "../Utility/Files.hpp"
#include "../Utility/JsonHandler.hpp"
#include "PlotViewer.hpp"
#include "../Core/App.hpp"
#include "MainLayer.hpp"

void FileManagerLayer::OnRender()
{
	ImGui::Begin("File Manager");

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
		if (ImGui::Button("Use selected for data"))
		{
			// read content of json file and assign read data to current plot data (PlotViewer)
			auto json_content = JSON_Handler::ReadJsonFile(_selected_file);
			auto viewer = App::Instance().GetWindow().GetLayer<MainLayer>(LayerType::Main)->GetPlotViewer();
			viewer->SetPlotData(json_content);
		}
	}

	ImGui::End();
}


