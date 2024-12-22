#include "FileManagerLayer.hpp"

#include "imgui.h"
#include <iostream>

#include <fstream>

#include "nlohmann/json.hpp"


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
	ImGui::Text("JSON");

	if (ImGui::BeginChild("DropArea", ImVec2(0, 100), true))
	{
		ImGui::Text("Test");
		HandleDragAndDrop();
		ImGui::EndChild();
	}

	
	
	/*ImGui::Begin("FileManagerLayer");
	
	if (ImGui::Button("Open JSON file"))
	{
		std::cout << "Button clicked!\n";
		OpenFileDialog();
		
	}
	ImGui::End();*/

}


