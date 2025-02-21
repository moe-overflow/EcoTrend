#pragma once

#include "../../Data/PlotData.hpp"
#include "../ChartType.hpp"
#include "../Layer.hpp"

class Popup : public Layer
{
public:
    virtual ~Popup() = default;

    [[nodiscard]] LayerType GetType() const override
    {
        return LayerType::Popup;
    }
};

class ExportReportPopup final : public Popup
{
public:
    void OnRender() override;

    void SetPlotData(PlotData data)
    {
        _data = std::move(data);
    }

    std::string GetPlotName()
    {
        return _image_name;
    }

private:
    PlotData _data;

    std::string _image_name;
};

class InsertJsonDirPopup final : public Popup
{
public:
    void OnRender() override;

private:
    std::string _inserted_file_name;
};

class SaveChartPopup final : public Popup
{
public:
    void OnRender() override;
};

class SelectChartTypePopup final : public Popup
{
public:
    void OnRender() override;

    [[nodiscard]] ChartType GetCurrent() const;

    void DeselectChartType();

private:
    bool _show;
    int _selected_chart = -1;

    const std::array<std::string, 1> _chart_types{ "Line Chart" };
};

class SelectDataSourcePopup final : public Popup
{
public:
    inline void OnRender() override;
};
