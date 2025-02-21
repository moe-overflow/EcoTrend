#pragma once

#include <nlohmann/json.hpp>
#include <fstream>

struct TextSettings
{
	std::string FontFamily;
	size_t FontSize;
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

	Template(const std::string& template_file_name);

	[[nodiscard]] TemplateStruct& Get() { return _template_struct; }

private:
	nlohmann::json _template_file;

	TemplateStruct _template_struct;

	void Apply();

};

