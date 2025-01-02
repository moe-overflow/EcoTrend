#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Layer.hpp"
#include "Popup/InsertJsonDirPopup.hpp"
#include "PlotViewer.hpp"

class FileManagerLayer : public Layer
{
public:
	virtual void OnRender() override;

    [[nodiscard]] LayerType GetType() const override { return LayerType::FileManagerLayer; }

private:
	// std::vector<std::string> _recent_files;

    // todo: pasting path of directory not working in GUI
    std::string _current_folder = R"(C:\Users\MOE\Desktop\EcoCollectorApp)";

    std::string _selected_file;
    std::unique_ptr<InsertJsonDirPopup> _insert_dir_popup = std::make_unique<InsertJsonDirPopup>();
};
