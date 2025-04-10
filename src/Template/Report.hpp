#pragma once

#include <hpdf.h>
#include <hpdf_types.h>
#include <iostream>
#include <string>

#include "../Template/Template.hpp"
#include "../Data/StatisticCalculation.hpp"

namespace
{
    void PdfErrorHandler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data)
    {
        std::cerr << "ERROR: "
                  << "error_no = " << std::hex << error_no << ","
                  << "detail_no = " << std::dec << detail_no << std::endl;
    }
} // namespace

struct Position final
{
    float X, Y;
};

class Report
{
public:
    Report(std::string const& file_name, Statistics const& statistics, std::shared_ptr<Template> const& pdf_template);

    ~Report();

    void Create() const;

    void Save();

private:
    void AddHeader() const;

    void AddTrendPlot() const;

    void AddStatisticsPlot() const;

    void AddFooter() const;

    /**/

    void DrawImage(std::string const& image_path, Position const& position, float height_ratio) const;

    void DrawText(std::string const& text, Position& position, TextAttributes& settings) const;

    void DrawSeparator(int y) const;

private:
    struct PageSettings
    {
        float Width, Height;
        HPDF_Font FontHandler;
    };


    std::string _file_name;
    HPDF_Doc _document;
    HPDF_Doc _page;
    PageSettings _page_settings;


    std::shared_ptr<Template> _template;

    Statistics const& _statistics;

};
