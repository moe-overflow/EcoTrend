#include "PdfFile.hpp"
#include "JsonHandler.hpp"

PdfFile::PdfFile(const std::string file_name, const Template pdf_template)
    : _document{ HPDF_New(PdfErrorHandler, nullptr) },
      _template{ std::make_unique<Template>(pdf_template) },
      _file_name{ file_name }
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

PdfFile::~PdfFile()
{
    HPDF_Free(_document);
}

void PdfFile::Create() const
{
    AddHeader();
    AddTrendPlot();
    AddStatisticsPlot();
    AddFooter();
}

// TODO: Header information as a struct (parameter) + title
void PdfFile::AddHeader() const
{
    // Title
    Position pos{ 60, 800 };
    DrawText("Extrusion Process Report", pos, _template->Get().TitleTextSettings);

    // Logo
    std::string image_path = std::string(ASSETS_PATH) + '/' + _template->Get().LogoImageName.c_str() + ".png";
    auto json = JSON_Handler::ReadJsonFile(std::string(TEMPLATE_PATH) + "/debug.json");
    pos = { json["Logo"]["x"], json["Logo"]["y"] };
    DrawImage(image_path, pos, .10F);

    // Meta data / header information
    pos = { 60, 770 };
    DrawText("Start at: 08.03.2023 12:34", pos, _template->Get().HeaderTextSettings);
}

void PdfFile::AddTrendPlot() const
{
    auto json = JSON_Handler::ReadJsonFile(std::string(TEMPLATE_PATH) + "/debug.json");

    Position pos{ json["MeasurementTitle"]["x"], json["MeasurementTitle"]["y"] };
    DrawText("OUTER DIAMETER", pos, _template->Get().MeasurementTitleSettings);

    pos = { json["TrendPlot"]["x"], json["TrendPlot"]["y"] };
    DrawImage(_file_name + ".png", pos, .33F);
}

void PdfFile::AddStatisticsPlot() const
{
    auto json = JSON_Handler::ReadJsonFile(std::string(TEMPLATE_PATH) + "/debug.json");

    Position pos{ json["StatisticsPlot"]["x"], json["StatisticsPlot"]["y"] };
    DrawImage(_file_name + "_statistics.png", pos, .30F);

    // TODO: Add here text of statistic value
}

void PdfFile::AddFooter() const
{
    auto json = JSON_Handler::ReadJsonFile(std::string(TEMPLATE_PATH) + "/debug.json");
    auto x_array = json["Footer"]["x"];

    TextSettings text_settings = _template->Get().FooterTextSettings;

    // TODO: Separating line

    // Left
    Position pos = { x_array["Left"], json["Footer"]["y"] };
    DrawText("Left", pos, text_settings);

    // Center
    pos.X = x_array["Center"];
    DrawText("Center", pos, text_settings);

    // Right
    pos.X = x_array["Right"];
    DrawText("Right", pos, text_settings);
}

void PdfFile::DrawText(std::string const& text, Position& position, TextSettings& settings) const
{
    HPDF_Font font = HPDF_GetFont(_document, settings.FontFamily.c_str(), nullptr);

    HPDF_Page_BeginText(_page);
    HPDF_Page_MoveTextPos(_page, position.X, position.Y);

    HPDF_Page_SetFontAndSize(_page, font, settings.FontSize);

    HPDF_Page_ShowText(_page, text.c_str());

    HPDF_Page_EndText(_page);
}

void PdfFile::DrawImage(std::string const& image_path, Position const& position, float height_ratio) const
{
    HPDF_Image image = HPDF_LoadPngImageFromFile(_document, image_path.c_str());

    size_t image_width{ HPDF_Image_GetWidth(image) }, image_height{ HPDF_Image_GetHeight(image) };

    // std::cout << "Loaded image (w: " << image_width << ", h: " << image_height << ")" << std::endl;

    float const aspect_ratio{ (float) image_width / (float) image_height };
    HPDF_Page_SetLineWidth(_page, 0.5);

    float new_height = _page_settings.Height * height_ratio;
    HPDF_Page_DrawImage(_page, image, position.X, position.Y, new_height * aspect_ratio, float(new_height));
}

void PdfFile::Save()
{
    HPDF_SaveToFile(_document, (_file_name + ".pdf").c_str());
}
