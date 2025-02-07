#pragma once

#include <memory>

#include "Layer.hpp"
#include "Popup/SelectChartTypePopup.hpp"
#include "Popup/SaveChartPopup.hpp"
#include "../Utility/JsonHandler.hpp"
#include "Canvas/Canvas.hpp"

class PlotViewer : public Layer
{
public:
	virtual void OnRender() override;

	[[nodiscard]] LayerType GetType() const override { return LayerType::PlotViewer; }

	void SetPlotData(const std::vector<DataPoint>& data);


private:

	std::unique_ptr<SelectChartTypePopup> _select_chart_type_popup = std::make_unique<SelectChartTypePopup>();
	std::unique_ptr<SaveChartPopup> _save_chart_popup = std::make_unique<SaveChartPopup>();

	std::vector<DataPoint> _current_data;

	std::vector<double> _x_values;
	std::vector<double> _y_values;

	/**/

	std::unique_ptr<Canvas> _canvas = std::make_unique<Canvas>();

};

