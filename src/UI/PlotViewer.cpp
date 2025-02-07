#include "PlotViewer.hpp"

#include "imgui.h"
#include "implot.h"
#include "Popup/SelectChartTypePopup.hpp"
#include "../Utility/PlotExporter.hpp"

using namespace ImGui;
using namespace ImPlot;

void PlotViewer::OnRender()
{
	Begin("Plot");
	{
		using namespace ImPlot;

		// Obere Leiste
		{
			_select_chart_type_popup->OnRender();
			if (Button("Deselect current chart type")) { _select_chart_type_popup->DeselectChartType(); }
		}

		auto s = _select_chart_type_popup->GetCurrent();

		switch (s)
		{
		case ChartType::None:
			// todo: render default empty screen
			break;

		case ChartType::LineChart:
			// static ImPlotAxisFlags axis_flags = ImPlotAxisFlags_NoTickLabels;
			if (BeginPlot("Test"))
			{
				//SetupAxes(nullptr, nullptr, axis_flags, axis_flags);
				//SetupAxisLimits();

				PlotLine("Data", _x_values.data(), _y_values.data(), static_cast<int>(_x_values.size()));

				if (Button("Save as Image"))
				{
					auto limits = ImPlot::GetPlotLimits();
					PlotExporter::ExportPlot(_x_values, _y_values, limits.X.Min, limits.X.Max, limits.Y.Min, limits.Y.Max);
				}
				EndPlot();

			}
			break;

		default:
			break;
		}
	}
	End();
}

void PlotViewer::SetPlotData(const std::vector<DataPoint>& data)
{
	_current_data = data;
	for (size_t i = 0; i < _current_data.size(); i++)
	{
		_x_values.push_back(static_cast<double>(i));
		_y_values.push_back(_current_data[i].value);
	}
}
