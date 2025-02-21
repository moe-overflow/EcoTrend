#pragma once

#include <string>
#include <imgui.h>
#include <imgui_stdlib.h>
#include "../../Utility/PlotExporter.hpp"
#include "../Layer.hpp"
#include "../../Utility/PdfFile.hpp"
#include "../../Data/StatisticCalculation.hpp"


inline constexpr auto SIKORA_TEMPLATE_FILE_NAME{ "sikora_template" };

namespace
{
    float selected_color[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
    std::string str_color = "blue"; // default color
}

class ExportReportPopup : public Layer
{
public:
    inline virtual void OnRender() override
    {
        using namespace ImGui;
        if (Button("Generate report"))
        {
            OpenPopup("ExportReportPopup");
        }

        if (BeginPopupModal("ExportReportPopup", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f)); // Dark background
            PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f); // Rounded corners
            PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10)); // Padding

            Text("Modify report settings");


            //Checkbox("Enable Feature", &_include_statistics);


            //// todo: dialogue with text filed for plot name
            //std::string plot_title = "myPlot";
            //_plot_data._ImagePath = plot_title;

            ImGui::InputText("Text", &_image_name);

            // std::cout << "image name: " << image_name << std::endl;

            {
                ImGui::ColorPicker4("Pick Line Color", selected_color);

                // Apply the selected color to the plot
                str_color = "rgba(" +
                    std::to_string(int(selected_color[0] * 255)) + "," +
                    std::to_string(int(selected_color[1] * 255)) + "," +
                    std::to_string(int(selected_color[2] * 255)) + "," +
                    std::to_string(selected_color[3]) + ")";
            }

            /**/
            Separator();
            /**/
            if (Button("Ok"))
            {
                _data._ImagePath = _image_name;
                PlotExporter::ExportPlot(_data._ImagePath, _data._Timestamps, _data._Values, _data._PlotLimits, str_color);
                
                // Statistics
                {
                    // todo / consideration: Shouldn't this be called before exporting the plot since 
                    // plot should include some statistics values
                    auto statistics = StatisticCalculation::CalculateStatistics(_data._Values, { 17000, 16000, 18000 });
                


                }


                // Generate PDF
                {
                    // TODO: find out template to use and set it here
                    Template templ{ std::string(TEMPLATE_PATH) + "/" + SIKORA_TEMPLATE_FILE_NAME + ".json" };
                    PdfFile pdf(_data._ImagePath, templ);
                    pdf.Create();
                    pdf.Save();
                }
                
                CloseCurrentPopup();
            }
            SameLine();
            if (Button("Cancel"))
            {
                CloseCurrentPopup();
            }
            PopStyleVar(2);
            PopStyleColor();

            EndPopup();
        }

    }

    [[nodiscard]] LayerType GetType() const override { return LayerType::Popup; }

    void SetPlotData(PlotData data) 
    {
        _data = data;
    }

    std::string GetPlotName() { return _image_name; }

private:

    bool _include_statistics = false;

    PlotData _data;

    std::string _image_name;

};

