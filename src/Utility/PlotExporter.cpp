#include "PlotExporter.hpp"

#include "JsonHandler.hpp"
#include <matplot/matplot.h>

using namespace matplot;

bool PlotExporter::ExportPlot(std::string const& file_name, Dataset const& dataset, PlotLimits const& limits)
{
    auto json = JSON_Handler::ReadJsonFile(std::string(TEMPLATE_PATH) + "/plot_debug.json");

    auto const& settings = json["trend"];

    auto fig = figure(true);
    auto ax = fig->add_axes();

    // todo: use color parameter (string or rgba?)

    std::string color = settings["color"];
    ax->plot(dataset.first, dataset.second)->line_width(settings["line_width"]).color(color);

    ax->xlim({ limits.x_min, limits.x_max });
    ax->ylim({ limits.y_min, limits.y_max });

    ax->font_size(settings["font_size"]);
    //ax->font_weight(settings["font_weight"]);

    // ax->x2label("");
    // ax->y2label("");
    fig->size(settings["resolution"]["x"], settings["resolution"]["y"]);

    auto result = fig->save(file_name + ".png");

    /*
        The first attmept to save the image fails because image is only saved
        correctly to file system after appliction has been terminated.
        As a temporary solution, a second copy (of jpg format) of the image is stored, too.
    */
    fig->save(file_name + "_d.jpg");

    return result;
}

bool PlotExporter::ExportStatisticsPlot(std::string const& file_name, StatisticCalculation::Axes const& axes)
{
    auto json = JSON_Handler::ReadJsonFile(std::string(TEMPLATE_PATH) + "/plot_debug.json");
    auto const& settings = json["statistics"];

    auto fig = figure(true);
    auto ax = fig->add_axes();

    std::string color = settings["color"];
    int line_width = settings["line_width"];
    ax->bar(axes.first, axes.second)->line_width(line_width).face_color(color);
    ax->legend();

    /**/
    std::vector<double> x_ticks;
    for (size_t i = 0; i < StatisticCalculation::STEP_SIZE + 1; i++)
    {
        if (i % 4 == 0)
        {
            x_ticks.push_back(axes.first[i]);
        }
    }
    ax->xticks(x_ticks);


    ax->yticks({ 0, 25, 50, 75, 100 });
    ax->ylim({ 0.0, 100.00 });

    int font_size = settings["font_size"];
    ax->font_size(font_size);
    //xlabel("Bins");
    //ylabel("%");

    ax->font(""); // ?
    ax->title_font_weight();

    /**/

    int x = settings["resolution"]["x"], y = settings["resolution"]["y"];
    fig->size(x, y);
    int font_size2 = settings["fig_font_size"];
    fig->font_size(font_size2);

    auto result = fig->save(file_name + ".png");

    /*
        The first attmept to save the image fails because image is only saved
        correctly to file system after appliction has been terminated.
        As a temporary solution, a second copy (of jpg format) of the image is stored, too.
    */
    fig->save(file_name + "_d.jpg");

    return result;
}
