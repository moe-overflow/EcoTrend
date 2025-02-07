#pragma once

#include <memory>

#include "Layer.hpp"
#include "PlotViewer.hpp"
#include "Canvas/CanvasLayer.hpp"

enum class RenderMode
{
	None = 0,
	PlotViewer,
	Canvas
};


class MainLayer : public Layer
{
public:
	virtual void OnRender() override;

	[[nodiscard]] LayerType GetType() const override { return LayerType::Main; }

	[[nodiscard]] PlotViewer* GetPlotViewer() { return _plot_viewer.get(); }

private:
	RenderMode _mode = RenderMode::None; 
	
	std::unique_ptr<PlotViewer> _plot_viewer = std::make_unique<PlotViewer>();

	std::unique_ptr<CanvasLayer> _canvas_layer = std::make_unique<CanvasLayer>();

};
