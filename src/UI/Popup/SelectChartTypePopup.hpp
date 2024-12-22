#pragma once

#include <array>
#include <string>

#include "../Layer.hpp"
#include "imgui.h"

#include "../PlotViewer.hpp"
#include "../ChartType.hpp"

class SelectChartTypePopup : public Layer
{
public:
	inline virtual void OnRender() override
	{
        if (ImGui::Button("Choose chart type"))
        {
            ImGui::OpenPopup("Select Item Popup");
        }

        if (ImGui::BeginPopup("Select Item Popup"))
        {
            for (size_t i = 0; i < _chart_types.size(); i++)
            {
                if (ImGui::Selectable(_chart_types[i].c_str(), _selected_chart == i))
                {
                    _selected_chart = i;
                    ImGui::CloseCurrentPopup();
                }
            }

            ImGui::EndPopup();
        }
    }

public:

    [[nodiscard]] ChartType GetCurrentChartType() const
    {
        switch (_selected_chart)
        {
        case 0:
            return ChartType::LineChart;

        default:
            return ChartType::None;
        }
    }
    
    inline void DeselectChartType() { _selected_chart = -1; }

private:
	bool _show;
	int _selected_chart = -1;
	
	const std::array<std::string, 1> _chart_types
	{
		"Line Chart"
	};




};