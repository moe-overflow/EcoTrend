#include "PlotViewer.hpp"

#include "../../Utility/PlotExporter.hpp"
#include "../Popup/Popup.hpp"
#include "imgui.h"
#include "implot.h"

using namespace ImGui;
using namespace ImPlot;

void PlotViewer::OnRender()
{
    Begin("Plot");
    {
        auto window_size = GetWindowSize();
        ImPlotRect current_limits;

        if (BeginPlot("Plot Viewer", ImVec2(window_size.x, window_size.y * .90F)))
        {
            //SetupAxes(nullptr, nullptr, axis_flags, axis_flags);
            //SetupAxisLimits();
            PlotLine(
                    "Trend Data",
                    _plot_data._Timestamps.data(),
                    _plot_data._Values.data(),
                    static_cast<int>(_plot_data._Values.size())
            );

            // SetNextPlotTicksX(timestamps.data(), time_labels.data(), timestamps.size(), ImPlot::TickFormatter);
            current_limits = ImPlot::GetPlotLimits();
            EndPlot();
        }


        //	// capture current limits to dataset
        _plot_data._PlotLimits = { current_limits.X.Min,
                                   current_limits.X.Max,
                                   current_limits.Y.Min,
                                   current_limits.Y.Max

        };

        this->UpdatePlotName(_export_report_popup->GetPlotName());
        _export_report_popup->SetPlotData(_plot_data);

        _export_report_popup->OnRender();
    }
    End();
}

void PlotViewer::SetPlotData(nlohmann::json const& data)
{
    _plot_data._Values.clear();
    _plot_data._Timestamps.clear();

    int counter{ 0 };
    for (auto const& entry : data)
    {
        //auto timestamp = JSON_Handler::ParseTimestamp(entry["_time"]);
        //_plot_data.Timestamps.push_back();


        _plot_data._Timestamps.push_back(counter);
        counter++;

        _plot_data._Values.push_back(std::stod(entry["_value"].get<std::string>()));
    }

    // Auto fit axes
    ImPlot::SetNextAxesToFit();

}

