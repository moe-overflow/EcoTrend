#pragma once

#include "../../Data/PlotData.hpp"
#include "../Layer/Layer.hpp"

class Popup : public Layer
{
public:
    ~Popup() override = default;

    [[nodiscard]] LayerType GetType() const override
    {
        return LayerType::Popup;
    }
};

class ExportReportPopup final : public Popup
{
public:
    void OnRender() override;

    void OnExportReport() const;

    void SetPlotData(PlotData data)
    {
        _data = std::move(data);
    }

    std::string GetPlotName()
    {
        return _image_name;
    }

private:
    PlotData _data{};

    std::string _image_name;

    /**/

    void OnGenerateReport(std::string const& title, Statistics const& statistics) const;

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

class SelectDataSourcePopup final : public Popup
{
public:
    inline void OnRender() override;
};
