#include "Popup.hpp"

#include <imgui.h>
#include <imgui_stdlib.h>
#include <string>

#include "../../Core/App.hpp"
#include "../../Template/Report.hpp"
#include "../../Utility/PlotExporter.hpp"


void ExportReportPopup::OnRender()
{
    using namespace ImGui;
    if (Button("Generate Report"))
    {
        OpenPopup("Generating Report");
    }

    if (BeginPopupModal("Generating Report", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f)); // Dark background
        PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);                    // Rounded corners
        PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));             // Padding

        Text("Modify report settings");


        //Checkbox("Enable Feature", &_include_statistics);


        //// todo: dialogue with text filed for plot name
        //std::string plot_title = "myPlot";
        //_plot_data._ImagePath = plot_title;

        // TODO: Label is to be placed to the right of input field
        InputText("Enter Report Name", &_image_name);

        // std::cout << "image name: " << image_name << std::endl;

        if (RadioButton("Use SIKORA template", App::Instance().UsingSikoraTemplate()))
        {
            App::Instance().SetUsingSikoraTemplate(true);
        }
        SameLine();
        if (RadioButton("Use custom template", !App::Instance().UsingSikoraTemplate()))
        {
            App::Instance().SetUsingSikoraTemplate(false);
        }

        /**/
        Separator();
        /**/
        if (Button("Ok"))
        {
            _data._ImagePath = _image_name;
            OnExportReport();
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

void ExportReportPopup::OnExportReport() const
{
    std::shared_ptr<Template> templ = App::Instance().UsingSikoraTemplate() ? App::Instance().GetSikoraTemplate()
                                                                            : App::Instance().GetCustomerTemplate();
    
    // Statistics
    // todo / consideration: Shouldn't this be called before exporting the plot since
    // plot should include some statistics values
    Statistics const statistics = StatisticCalculation::CalculateStatistics(_data._Values, { 17000, 16000, 18000 });

    PlotExporter::ExportPlot(_data._ImagePath, { _data._Timestamps, _data._Values }, _data._PlotLimits);

    PlotExporter::ExportStatisticsPlot(
            _data._ImagePath + "_statistics",
            StatisticCalculation::DetermineAxes(statistics, _data._Values)
    );

    // TODO: Timer for waiting for images to be exported
    //OnGenerateReport(_data._ImagePath, statistics);
    //Report report(title, templ, statistics);
     
    Report report(_data._ImagePath, statistics, templ);
    report.Create();
    report.Save();
}

void ExportReportPopup::OnGenerateReport(std::string const& title, Statistics const& statistics) const { }
