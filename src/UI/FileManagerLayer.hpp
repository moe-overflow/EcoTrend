#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Layer.hpp"
#include "Popup/InsertJsonDirPopup.hpp"

class FileManagerLayer : public Layer
{
public:
	virtual void OnRender() override;


private:
	// std::vector<std::string> _recent_files;

    std::string _current_folder = R"(C:\Development\Cpp\LL)";
    std::string _selected_file;
    std::unique_ptr<InsertJsonDirPopup> _insert_dir_popup = std::make_unique<InsertJsonDirPopup>();
};
