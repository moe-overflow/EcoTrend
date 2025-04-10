#pragma once

#include <algorithm>
#include <fstream>
#include <magic_enum/magic_enum.hpp>
#include <nlohmann/json.hpp>

enum class FontFamilyOption
{
    Helvetica,
    Times_Roman,
    Courier,
    Symbol,
    ZapfDingbats,
    Times_BoldItalic,
    Times_Bold
};

static std::string FontFamilyEnumToString(FontFamilyOption enum_element)
{
    return std::string(magic_enum::enum_name(enum_element));
}

static FontFamilyOption FontFamilyStringToEnum(std::string& str)
{
    // Font families use hyphen instead of underscore, so it has to be
    // converted to an underscore because of enum class
    std::replace(str.begin(), str.end(), '-', '_');

    auto value = magic_enum::enum_cast<FontFamilyOption>(str);

    if (value.has_value())
        return value.value();

    throw std::runtime_error("Unknown Font Family!");
}

struct Color final
{
    float R, G, B;
};

// TODO: Rename to TextAttributes
struct TextAttributes
{
    FontFamilyOption FontFamily;
    int FontSize;
    Color FontColor;

    // bool FontBold;
    // bool FontItalic;
};

struct PlotAttributes
{
    // size_t X, Y;
    // size_t FontSize;
    Color CurveColor;
    size_t LineWidth;
};

// TODO: Rename to TemplateAttributes
struct TemplateStruct
{
    TextAttributes TitleTextSettings;

    std::string LogoImageName;

    TextAttributes HeaderTextSettings;

    TextAttributes MeasurementTitleSettings;

    PlotAttributes TrendPlotSettings;
    PlotAttributes StatisticsPlotSettings;

    TextAttributes StatisticsValuesSettings;

    TextAttributes FooterTextSettings;
};

class Template
{
public:
    Template() = delete;

    explicit Template(std::string const& template_file_name);

    Template(Template const&) = delete;
    Template& operator=(Template const&) = delete;

    Template(Template&&) = default;
    Template& operator=(Template&&) = default;

    [[nodiscard]] std::shared_ptr<TemplateStruct> Get()
    {
        return _template_struct;
    }

    void ApplyToJson(std::shared_ptr<TemplateStruct> template_struct);

private:
    std::unique_ptr<nlohmann::json> _template_file;

    std::shared_ptr<TemplateStruct> _template_struct;

    void Apply(); // should be renamed since from json to struct!

    TextAttributes ConstructTextSettings(std::string const& name);

    PlotAttributes ConstructPlotSettings(std::string const& name);

    void OverrideTextSettings(TextAttributes const& settings, std::string const& field_name);

    void OverridePlotSettings(PlotAttributes const& settings, std::string const& field_name);

};
