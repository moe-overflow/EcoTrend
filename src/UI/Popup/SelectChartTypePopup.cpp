#include "Popup.hpp"

#include "imgui.h"

void SelectChartTypePopup::OnRender()
{
    if (ImGui::Button("Open Popup"))
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

ChartType SelectChartTypePopup::GetCurrent() const
{
    switch (_selected_chart)
    {
        case 0:
            return ChartType::LineChart;

        default:
            return ChartType::None;
    }
}

void SelectChartTypePopup::DeselectChartType()
{
    _selected_chart = -1;
}
