#pragma once


enum class LayerType
{
	Dockspace,
	PlotViewer,
	MenuBar,
	FileManagerLayer,
	Main,
	Popup,
	Canvas

	//    InsertJsonDirPopup,
	//    SaveChartPopup,
	//    SelectChartTypePopup,
	//    SelectDataSourcePopup
};

class Layer
{
public:
	virtual ~Layer() = default;

	virtual void OnRender() {};
	virtual void OnUpdate() {};

	[[nodiscard]] virtual LayerType GetType() const = 0;
};

class Dockspace : public Layer
{
public:
	virtual void OnRender() override;

	[[nodiscard]] LayerType GetType() const override { return LayerType::Dockspace; }

private:
	bool _full_screen = true;
};

class MenuBar : public Layer
{
public:
	virtual void OnRender() override;

	[[nodiscard]] LayerType GetType() const override { return LayerType::MenuBar; }
};

