#include "PlotViewer.hpp"

#include "imgui.h"
#include "implot.h"

#include "ChartType.hpp"

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
		using namespace ImPlot;

		// Obere Leiste
		{
			_select_chart_type_popup->OnRender();
			if (Button("Deselect current chart type")) { _select_chart_type_popup->DeselectChartType(); }
		}

        auto s = _select_chart_type_popup->GetCurrentChartType();
        switch (s) {
            case ChartType::None:
                break;

            case ChartType::LineChart:
                static ImPlotAxisFlags axis_flags = ImPlotAxisFlags_NoTickLabels;
                if (BeginPlot("Test"))
                {
                    //SetupAxes(nullptr, nullptr, axis_flags, axis_flags);
                    //SetupAxisLimits();
                    int data[5] = { 15, 23, 62, 11, 512 };
                    PlotBars("MyPlot", data, 5);
                    EndPlot();

                }
                break;
        }

        //_save_chart_popup->OnRender();

	}
	End();
}

void PlotViewer::OnRenderCanvas()
{
//	if(BeginChild("Canvas", ImVec2(800, 600), true, ImGuiWindowFlags_NoMove))
//    {
//
//    }
//
//	EndChild();


    Begin("Test");
    End();
}
