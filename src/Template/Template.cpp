#include "Template.hpp"

#include "../Core/App.hpp"
#include "../Utility/JsonHandler.hpp"
#include <iostream>

using json = nlohmann::json;

Template::Template(std::string const& template_file_name)
{
    _template_file = std::make_unique<json>(std::move(JSON_Handler::ReadJsonFile(template_file_name)));
    // _template_struct = std::make_shared<TemplateStruct>();

    try
    {
        Apply();
    }
    catch (std::exception& e)
    {
        std::cerr << "Apply(): " << e.what() << std::endl;
    }
}

void Template::ApplyToJson(std::shared_ptr<TemplateStruct> template_struct)
{
    OverrideTextSettings(template_struct->TitleTextSettings, "Title");
    OverrideTextSettings(template_struct->HeaderTextSettings, "Header");
    OverrideTextSettings(template_struct->MeasurementTitleSettings, "MeasurementTitle");
    OverrideTextSettings(template_struct->StatisticsValuesSettings, "StatisticsValues");
    OverrideTextSettings(template_struct->FooterTextSettings, "Footer");

    OverridePlotSettings(template_struct->TrendPlotSettings, "TrendPlot");
    OverridePlotSettings(template_struct->StatisticsPlotSettings, "StatisticsPlot");

    _template_file->at("Logo").at("ImageName") = template_struct->LogoImageName;

    std::cout << *_template_file << std::endl;


    JSON_Handler::WriteJsonFile(*_template_file.get(), App::CUSTOMER_TEMPLATE_PATH);

    Apply(); // ? In order to read from json
}

void Template::Apply() // Json to struct
{
    TemplateStruct ts{};

    ts.TitleTextSettings = ConstructTextSettings("Title");
    ts.LogoImageName = _template_file->at("Logo").at("ImageName");
    ts.HeaderTextSettings = ConstructTextSettings("Header");
    ts.MeasurementTitleSettings = ConstructTextSettings("MeasurementTitle");
    ts.TrendPlotSettings = ConstructPlotSettings("TrendPlot");
    ts.StatisticsPlotSettings = ConstructPlotSettings("StatisticsPlot");
    ts.StatisticsValuesSettings = ConstructTextSettings("StatisticsValues");
    ts.FooterTextSettings = ConstructTextSettings("Footer");

    _template_struct = std::make_shared<TemplateStruct>(ts);
}

TextAttributes Template::ConstructTextSettings(std::string const& name)
{
    return { FontFamilyStringToEnum(_template_file->at(name).at("FontFamily").get<std::string>()),
             _template_file->at(name).at("FontSize"),
             _template_file->at(name).at("FontColor").at("R"),
             _template_file->at(name).at("FontColor").at("G"),
             _template_file->at(name).at("FontColor").at("B") };
}

PlotAttributes Template::ConstructPlotSettings(std::string const& name)
{
    return { _template_file->at(name).at("CurveColor").at("R"),
             _template_file->at(name).at("CurveColor").at("G"),
             _template_file->at(name).at("CurveColor").at("B"),
             _template_file->at(name).at("LineWidth") };
}

void Template::OverrideTextSettings(TextAttributes const& settings, std::string const& field_name)
{
    _template_file->at(field_name).at("FontFamily") = FontFamilyEnumToString(settings.FontFamily);
    _template_file->at(field_name).at("FontSize") = settings.FontSize;

    _template_file->at(field_name).at("FontColor").at("R") = static_cast<int>(settings.FontColor.R);
    _template_file->at(field_name).at("FontColor").at("G") = static_cast<int>(settings.FontColor.G);
    _template_file->at(field_name).at("FontColor").at("B") = static_cast<int>(settings.FontColor.B);
}

void Template::OverridePlotSettings(PlotAttributes const& settings, std::string const& field_name)
{
    _template_file->at(field_name).at("CurveColor").at("R") = static_cast<int>(settings.CurveColor.R);
    _template_file->at(field_name).at("CurveColor").at("G") = static_cast<int>(settings.CurveColor.G);
    _template_file->at(field_name).at("CurveColor").at("B") = static_cast<int>(settings.CurveColor.B);

    _template_file->at(field_name).at("LineWidth") = static_cast<int>(settings.LineWidth);
}
