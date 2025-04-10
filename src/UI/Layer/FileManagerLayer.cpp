#include "FileManagerLayer.hpp"

#include <imgui.h>

#include "../../Core/App.hpp"
#include "../../Utility/Files.hpp"
#include "../../Utility/JsonHandler.hpp"

using namespace ImGui;

void FileManagerLayer::OnRender()
{
    Begin("File Manager");

    Text("Select A File To Import Data");
    // Text("Current directory: %s", _current_folder.c_str());
    // _insert_dir_popup->OnRender();
    
    std::vector<std::string> files = Files::GetJsonFiles(_current_folder);

    if (BeginListBox("Files:", ImVec2(-FLT_MIN, GetWindowSize().y * .75F)))
    {
        for (auto const& file : files)
        {
            bool is_selected = (file == _selected_file);
            if (Selectable(file.c_str(), is_selected))
            {
                _selected_file = file;
            }
        }

        EndListBox();
    }

    if (!_selected_file.empty())
    {
        std::shared_ptr<PlotViewer> plot_viewer = App::Instance().GetWindow().GetLayer<PlotViewer>(LayerType::PlotViewer);
        if (Button("Use selected for data"))
        {
            // Read JSON file and set its content for plotting
            auto json_content = JSON_Handler::ReadJsonFile(_selected_file);
            plot_viewer->SetPlotData(json_content);
        }
        SameLine();
        if (Button("Deselect"))
        {
            _selected_file = "";
            plot_viewer->SetPlotData({});
        }
    }

    End();

}
