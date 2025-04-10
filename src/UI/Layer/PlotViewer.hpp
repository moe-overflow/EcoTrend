#pragma once

#include <memory>

#include "Layer.hpp"
#include "../Popup/Popup.hpp"

#include "../../Data/PlotData.hpp"

class PlotViewer final : public Layer
{
public:
    void OnRender() override;

    [[nodiscard]] LayerType GetType() const override
    {
        return LayerType::PlotViewer;
    }

    void SetPlotData(nlohmann::json const& data);

    PlotData& GetPlotData()
    {
        return _plot_data;
    }

    void SetPlotName(std::string const& name)
    {
        _plot_data._ImagePath = name;
    }

private:

    std::unique_ptr<SaveChartPopup> _save_chart_popup = std::make_unique<SaveChartPopup>();

    std::unique_ptr<ExportReportPopup> _export_report_popup = std::make_unique<ExportReportPopup>();

    PlotData _plot_data{};

    /**/

    void UpdatePlotName(std::string const& new_name)
    {
        _plot_data._ImagePath = new_name;
    }
};
