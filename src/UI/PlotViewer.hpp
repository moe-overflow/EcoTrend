#pragma once

#include "Layer.hpp"
#include "Popup/SelectChartTypePopup.hpp"
#include "Popup/SaveChartPopup.hpp"

#include <memory>

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


private:

	RenderMode mode = RenderMode::None;

	void OnRenderPlotViewer();

	void OnRenderCanvas();

	std::unique_ptr<SelectChartTypePopup> _select_chart_type_popup = std::make_unique<SelectChartTypePopup>();
	//std::unique_ptr<SaveChartPopup> _save_chart_popup = std::make_unique<SaveChartPopup>();


};

