#pragma once

#include <memory>

#include "Layer.hpp"
#include "Popup/Popup.hpp"
#include "../Utility/JsonHandler.hpp"

#include "../Data/PlotData.hpp"

class PlotViewer : public Layer
{
public:
	void OnRender() override;

	[[nodiscard]] LayerType GetType() const override { return LayerType::PlotViewer; }

	void SetPlotData(const nlohmann::json& data); 
	PlotData& GetPlotData() { return _plot_data; }

	void SetPlotName(const std::string& name) { _plot_data._ImagePath = name; }

private:

	std::unique_ptr<SelectChartTypePopup> _select_chart_type_popup = std::make_unique<SelectChartTypePopup>();
	std::unique_ptr<SaveChartPopup> _save_chart_popup = std::make_unique<SaveChartPopup>();
	std::unique_ptr<ExportReportPopup> _export_report_popup = std::make_unique<ExportReportPopup>();


	PlotData _plot_data;

	/**/

	void UpdatePlotName(const std::string& new_name) { _plot_data._ImagePath = new_name; }

};

