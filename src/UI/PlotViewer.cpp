#include "PlotViewer.hpp"

#include "imgui.h"
#include "implot.h"

#include "ChartType.hpp"
#include "../Utility/PlotExporter.hpp"

using namespace ImGui;
using namespace ImPlot;

void PlotViewer::OnRender()
{
    Begin("Main");

	if (BeginTabBar("Switch"))
	{
		if(BeginTabItem("Plot")) 
		{
			OnRenderPlotViewer();
			EndTabItem();
		}
		if(BeginTabItem("Canvas")) 
		{
			OnRenderCanvas();
			EndTabItem();
		}

		EndTabBar();
	}

	End();
}


void PlotViewer::OnRenderPlotViewer()
{
    Begin("Plot");
	{

		// Obere Leiste
		{
			_select_chart_type_popup->OnRender();
			if (Button("Deselect current chart type")) { _select_chart_type_popup->DeselectChartType(); }

            Text("Selected data source: ");
			if (Button("Select data source"))
            {

            }
		}

        auto s = _select_chart_type_popup->GetCurrentChartType();
        switch (s)
		{
            case ChartType::None:
				// todo: empty screen
                break;

            case ChartType::LineChart:
                static ImPlotAxisFlags axis_flags = ImPlotAxisFlags_NoTickLabels;
				if (BeginPlot("Test"))
				{
                    PlotLine("Data", _x_values.data(), _y_values.data(), static_cast<int>(_x_values.size()) );

					if (Button("Save as Image"))
					{
						auto limits = ImPlot::GetPlotLimits();
                        PlotExporter::ExportPlot(_x_values, _y_values, limits.X.Min, limits.X.Max, limits.Y.Min, limits.Y.Max);
					}

					EndPlot();
				}
                break;
        }
        _save_chart_popup->OnRender();
	}
	End();
}

void PlotViewer::OnRenderCanvas()
{

    // Canvas Header
    {
        Begin("Canvas Header");

        if (Button("Add sample chart"))
            _canvas->AddImage("./sample_chart.png");

        End();
    }


    // Canvas
    {
        Begin("Canvas");

        // White background for canvas
        {
            auto p_min = ImGui::GetWindowPos();
            auto p_max = ImVec2(p_min.x + ImGui::GetWindowWidth(), p_min.y + ImGui::GetWindowHeight());

            auto draw_list = ImGui::GetWindowDrawList();
            draw_list->AddRectFilled(p_min, p_max, IM_COL32(255, 255, 255, 255));
        }
        _canvas->Render();


        End();
    }
}

void PlotViewer::SetPlotData(const std::vector<DataPoint>& data)
{
    _current_data = data;
    for(size_t i = 0; i < _current_data.size(); i++)
    {
        _x_values.push_back(static_cast<double>(i));
        _y_values.push_back(_current_data[i].value);
    }
}

