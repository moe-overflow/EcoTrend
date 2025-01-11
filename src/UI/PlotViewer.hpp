#pragma once

#include <memory>

#include "Layer.hpp"
#include "Popup/SelectChartTypePopup.hpp"
#include "Popup/SaveChartPopup.hpp"
#include "../Plot/PlotData.hpp"
#include "../Utility/JSON_Handler.hpp"
#include "Canvas/Canvas.hpp"

enum class RenderMode
{
	None = 0,
	PlotViewer,
	Canvas
};

class PlotViewer : public Layer
{
public:
	virtual void OnRender() override;

    [[nodiscard]] LayerType GetType() const override { return LayerType::PlotViewer; }

    void SetPlotData(const std::vector<DataPoint>& data);
private:

	RenderMode mode = RenderMode::None;

	void OnRenderPlotViewer();

	void OnRenderCanvas();

	std::unique_ptr<SelectDataSourcePopup> _select_chart_type_popup = std::make_unique<SelectDataSourcePopup>();
	std::unique_ptr<SaveChartPopup> _save_chart_popup = std::make_unique<SaveChartPopup>();

	// PlotData _current_data;

    std::vector<DataPoint> _current_data;

    std::vector<double> _x_values;
    std::vector<double> _y_values;

    std::unique_ptr<Canvas> _canvas = std::make_unique<Canvas>();
};

