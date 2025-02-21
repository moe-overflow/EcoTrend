#include "Template.hpp"

#include "../Utility/JsonHandler.hpp"
#include <iostream>

using json = nlohmann::json;

Template::Template(std::string const& template_file_name)
{
    _template_file = JSON_Handler::ReadJsonFile(template_file_name);
    Apply();
}


void Template::Apply()
{
    _template_struct.TitleTextSettings.FontFamily = _template_file["Title"]["FontFamily"];
    _template_struct.TitleTextSettings.FontSize = _template_file["Title"]["FontSize"];
    _template_struct.TitleTextSettings.FontColor = _template_file["Title"]["FontColor"];
    _template_struct.TitleTextSettings.FontBold = _template_file["Title"]["FontBold"];

    _template_struct.LogoImageName = _template_file["Logo"]["ImageName"];

    _template_struct.HeaderTextSettings.FontFamily = _template_file["Header"]["FontFamily"];
    _template_struct.HeaderTextSettings.FontSize = _template_file["Header"]["FontSize"];
    _template_struct.HeaderTextSettings.FontColor = _template_file["Header"]["FontColor"];
    _template_struct.HeaderTextSettings.FontBold = _template_file["Header"]["FontBold"];

    _template_struct.MeasurementTitleSettings.FontFamily = _template_file["MeasurementTitle"]["FontFamily"];
    _template_struct.MeasurementTitleSettings.FontSize = _template_file["MeasurementTitle"]["FontSize"];
    _template_struct.MeasurementTitleSettings.FontColor = _template_file["MeasurementTitle"]["FontColor"];
    _template_struct.MeasurementTitleSettings.FontBold = _template_file["MeasurementTitle"]["FontBold"];

    _template_struct.TrendPlotSettings.X = _template_file["TrendPlot"]["Position"]["X"];
    _template_struct.TrendPlotSettings.Y = _template_file["TrendPlot"]["Position"]["Y"];
    _template_struct.TrendPlotSettings.CurveColor = _template_file["TrendPlot"]["CurveColor"];

    _template_struct.StatisticsPlotSettings.X = _template_file["StatisticsPlot"]["Position"]["X"];
    _template_struct.StatisticsPlotSettings.Y = _template_file["StatisticsPlot"]["Position"]["Y"];
    _template_struct.StatisticsPlotSettings.CurveColor = _template_file["StatisticsPlot"]["CurveColor"];

    _template_struct.StatisticsValuesSettings.FontFamily = _template_file["StatisticsValues"]["FontFamily"];
    _template_struct.StatisticsValuesSettings.FontSize = _template_file["StatisticsValues"]["FontSize"];
    _template_struct.StatisticsValuesSettings.FontColor = _template_file["StatisticsValues"]["FontColor"];
    _template_struct.StatisticsValuesSettings.FontBold = _template_file["StatisticsValues"]["FontBold"];

    _template_struct.FooterTextSettings.FontFamily = _template_file["Footer"]["FontFamily"];
    _template_struct.FooterTextSettings.FontSize = _template_file["Footer"]["FontSize"];
    _template_struct.FooterTextSettings.FontColor = _template_file["Footer"]["FontColor"];
    _template_struct.FooterTextSettings.FontBold = _template_file["Footer"]["FontBold"];
}
