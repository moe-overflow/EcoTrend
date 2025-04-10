#include "Report.hpp"
#include "../Utility/JsonHandler.hpp"

#include <sstream>

Report::Report(
        std::string const& file_name,
        Statistics const& statistics,
        std::shared_ptr<Template> const& pdf_template
)
    : _document{ HPDF_New(PdfErrorHandler, nullptr) },
      _template{ pdf_template },
      _file_name{ file_name },
      _statistics{ statistics }
{
    if (!_document)
    {
        std::cerr << "Error: Couldn't create pdf" << std::endl;
        return;
    }

    _page = HPDF_AddPage(_document);

    HPDF_Page_SetSize(_page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    _page_settings.Height = HPDF_Page_GetHeight(_page);
    _page_settings.Width = HPDF_Page_GetWidth(_page);
}

Report::~Report()
{
    HPDF_Free(_document);
}

void Report::Create() const
{
    AddHeader();
    AddTrendPlot();
    AddStatisticsPlot();
    AddFooter();
}

// TODO: Header information as a struct (parameter) + title
void Report::AddHeader() const
{
    auto json = JSON_Handler::ReadJsonFile(std::string(TEMPLATE_PATH) + "/debug.json");

    // Title
    {
        Position pos{ 60, 800 };
        DrawText("Extrusion Process Report", pos, _template->Get()->TitleTextSettings);
    }

    // Logo
    {
        std::string image_path = std::string(ASSETS_PATH) + '/' + _template->Get()->LogoImageName.c_str() + ".png";
        Position pos = { json["Logo"]["x"], json["Logo"]["y"] };
        DrawImage(image_path, pos, .10F);
    }

    // Meta data / header information
    {
        Position pos = { json["Header"]["x_left"], json["Header"]["y_top"] };

        auto const& y_offset = json["Header"]["y_offset"];

        // TODO: retrieve meta data from database connection and draw them here

        // Left
        DrawText("Line: 523", pos, _template->Get()->HeaderTextSettings);
        pos.Y -= y_offset;
        DrawText("Recipe: Product: 1", pos, _template->Get()->HeaderTextSettings);
        pos.Y -= y_offset;
        DrawText("Operator: a", pos, _template->Get()->HeaderTextSettings);
        pos.Y -= y_offset;
        DrawText("Batch Nr.: 123456", pos, _template->Get()->HeaderTextSettings);
        pos.Y -= y_offset;

        // Right
        pos = { json["Header"]["x_right"], json["Header"]["y_top"] };

        DrawText("Start At: 22.01.2025 10:42", pos, _template->Get()->HeaderTextSettings);
        pos.Y -= y_offset;
        DrawText("End At: 22.01.2025 10:44", pos, _template->Get()->HeaderTextSettings);
        pos.Y -= y_offset;
        DrawText("Duration: 0.02 h", pos, _template->Get()->HeaderTextSettings);
        pos.Y -= y_offset;
        DrawText("Length: 102 m", pos, _template->Get()->HeaderTextSettings);
        pos.Y -= y_offset;
    }
}

void Report::AddTrendPlot() const
{
    auto json = JSON_Handler::ReadJsonFile(std::string(TEMPLATE_PATH) + "/debug.json");

    Position pos{ json["MeasurementTitle"]["x"], json["MeasurementTitle"]["y"] };
    DrawText("OUTER DIAMETER", pos, _template->Get()->MeasurementTitleSettings);

    DrawSeparator(pos.Y - 10);

    pos = { json["TrendPlot"]["x"], json["TrendPlot"]["y"] };
    DrawImage(_file_name + ".png", pos, .33F);
}

void Report::AddStatisticsPlot() const
{
    auto json = JSON_Handler::ReadJsonFile(std::string(TEMPLATE_PATH) + "/debug.json");

    Position pos{ json["StatisticsPlot"]["x"], json["StatisticsPlot"]["y"] };
    DrawImage(_file_name + "_statistics.png", pos, .30F);

    // Statistic value
    {

        pos = { json["StatisticsValues"]["x"], json["StatisticsValues"]["y_start"] };

        int const y_offset = json["StatisticsValues"]["y_offset"];
        TextAttributes& text_settings = _template->Get()->StatisticsValuesSettings;

        // TODO: add units

        DrawText("Nominal: " + std::to_string(_statistics.Nominal), pos, text_settings);
        pos.Y -= y_offset;
        DrawText("LSL: " + std::to_string(_statistics.LSL), pos, text_settings);
        pos.Y -= y_offset;
        DrawText("USL: " + std::to_string(_statistics.USL), pos, text_settings);
        pos.Y -= y_offset;
        DrawText("Mean Value: " + std::to_string(_statistics.Mean), pos, text_settings);
        pos.Y -= y_offset;
        DrawText("STD_Deviation: " + std::to_string(_statistics.STD_Deviation), pos, text_settings);
        pos.Y -= y_offset;
        DrawText("MinValue: " + std::to_string(_statistics.MinValue), pos, text_settings);
        pos.Y -= y_offset;
        DrawText("MaxValue: " + std::to_string(_statistics.MaxValue), pos, text_settings);
        pos.Y -= y_offset;
        DrawText("BelowLSL: " + std::to_string(_statistics.BelowLSL), pos, text_settings);
        pos.Y -= y_offset;
        DrawText("AboveUSL: " + std::to_string(_statistics.AboveUSL), pos, text_settings);
        pos.Y -= y_offset;
        DrawText("CP: " + std::to_string(_statistics.CP), pos, text_settings);
        pos.Y -= y_offset;
        DrawText("CPK: " + std::to_string(_statistics.CPK), pos, text_settings);
        pos.Y -= y_offset;
    }
}

void Report::AddFooter() const
{
    auto json = JSON_Handler::ReadJsonFile(std::string(TEMPLATE_PATH) + "/debug.json");

    int const separator_height = json["Footer"]["separator"];
    DrawSeparator(separator_height);

    auto& x_array = json["Footer"]["x"];

    TextAttributes text_settings = _template->Get()->FooterTextSettings;

    // Left
    Position pos = { x_array["Left"], json["Footer"]["y"] };
    DrawText("SIKORA", pos, text_settings);

    // Center
    pos.X = x_array["Center"];
    DrawText("ECOCONTROL Report", pos, text_settings);

    // Right
    pos.X = x_array["Right"];

    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&current_time), "%d.%m.%Y");

    DrawText(oss.str(), pos, text_settings);
}

void Report::DrawText(std::string const& text, Position& position, TextAttributes& settings) const
{
    HPDF_Font font = HPDF_GetFont(_document, FontFamilyEnumToString(settings.FontFamily).c_str(), nullptr);

    HPDF_Page_SetRGBFill(
            _page,
            settings.FontColor.R / 255.0F,
            settings.FontColor.G / 255.0F,
            settings.FontColor.B / 255.0F
    );

    HPDF_Page_BeginText(_page);
    HPDF_Page_MoveTextPos(_page, position.X, position.Y);

    HPDF_Page_SetFontAndSize(_page, font, settings.FontSize);

    HPDF_Page_ShowText(_page, text.c_str());

    HPDF_Page_EndText(_page);
}

void Report::DrawSeparator(int y) const
{
    auto json = JSON_Handler::ReadJsonFile(std::string(TEMPLATE_PATH) + "/debug.json");
    auto const& settings = json["Separator"];

    HPDF_Page_MoveTo(_page, settings["x_start"], y);
    HPDF_Page_LineTo(_page, settings["x_end"], y);
    HPDF_Page_Stroke(_page);
}

void Report::DrawImage(std::string const& image_path, Position const& position, float height_ratio) const
{
    HPDF_Image image = HPDF_LoadPngImageFromFile(_document, image_path.c_str());

    size_t image_width{ HPDF_Image_GetWidth(image) }, image_height{ HPDF_Image_GetHeight(image) };

    // std::cout << "Loaded image (w: " << image_width << ", h: " << image_height << ")" << std::endl;

    float const aspect_ratio{ (float) image_width / (float) image_height };
    HPDF_Page_SetLineWidth(_page, 0.5);

    float new_height = _page_settings.Height * height_ratio;
    HPDF_Page_DrawImage(_page, image, position.X, position.Y, new_height * aspect_ratio, float(new_height));
}

void Report::Save()
{
    HPDF_SaveToFile(_document, (_file_name + ".pdf").c_str());
}
