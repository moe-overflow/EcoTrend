#pragma once

#include <string>
#include <iostream>
#include <hpdf.h>
#include "../Template/Template.hpp"

namespace
{
    void PdfErrorHandler(
        HPDF_STATUS error_no,
        HPDF_STATUS detail_no,
        void* user_data)
    {
        std::cerr << "ERROR: " <<
            "error_no = " << std::hex << error_no << "," <<
            "detail_no = " << std::dec << detail_no << std::endl;
    }
}

struct Position final
{
    size_t X, Y;
};

class PdfFile
{
public:
    PdfFile(const std::string file_name, const Template pdf_template);

    ~PdfFile();

    void Create() const;

    void Save();

private:
    void AddHeader() const;

    void AddTrendPlot() const;

    /**/

    void DrawImage(const std::string& image_path, const Position& position, float height_ratio) const;

    void DrawText(const std::string& text, Position& position, TextSettings& settings) const;

private:

    struct PageSettings
    {
        int Width, Height;
        HPDF_Font FontHandler;
    };


	std::string _file_name;
    HPDF_Doc _document;
    HPDF_Doc _page;
    PageSettings _page_settings;


    std::unique_ptr<Template> _template;


};