#pragma once

#include <fstream>
#include <nlohmann/json.hpp>

struct TextSettings
{
    std::string FontFamily;
    float FontSize;
    std::string FontColor;
    bool FontBold;
};

struct PlotSettings
{
    size_t X, Y;
    std::string CurveColor;
};

struct TemplateStruct
{
    TextSettings TitleTextSettings;

    std::string LogoImageName;

    TextSettings HeaderTextSettings;

    TextSettings MeasurementTitleSettings;

    PlotSettings TrendPlotSettings;
    PlotSettings StatisticsPlotSettings;

    TextSettings StatisticsValuesSettings;

    TextSettings FooterTextSettings;
};

class Template
{
public:
    Template() = delete;

    Template(std::string const& template_file_name);

    [[nodiscard]] TemplateStruct& Get()
    {
        return _template_struct;
    }

private:
    nlohmann::json _template_file;

    TemplateStruct _template_struct;

    void Apply();
};
