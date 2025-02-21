#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Layer.hpp"
#include "PlotViewer.hpp"

class FileManagerLayer : public Layer
{
public:
	void OnRender() override;

	[[nodiscard]] LayerType GetType() const override { return LayerType::FileManagerLayer; }

private:
	std::vector<std::string> _recent_files;

	// Directory in which initially Json files will be searched
	std::string _current_folder = R"(D:\Trend)";

	std::string _selected_file;
	std::unique_ptr<InsertJsonDirPopup> _insert_dir_popup = std::make_unique<InsertJsonDirPopup>();


};
