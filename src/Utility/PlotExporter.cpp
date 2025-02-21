#include "PlotExporter.hpp"

#include <matplot/matplot.h>

using namespace matplot;

bool PlotExporter::ExportPlot(
    const std::string file_name,
    const std::vector<double>& x,
    const std::vector<double>& y,
    PlotLimits limits,
    const std::string color)
{
    // TODO: Create json config file for plot parameters

    auto fig = figure(true);
    auto ax = fig->add_axes();

    // todo: use color parameter (string or rgba?)
    ax->plot(x, y)->line_width(1).color("green");

    ax->xlim({ limits.x_min, limits.x_max });
    ax->ylim({ limits.y_min, limits.y_max });

    ax->font_size(14);

    // ax->x2label("");
    // ax->y2label("");


    fig->size(1000, 500);
    
    auto result = fig->save(file_name + ".png");
    
    /*
        The first attmept to save the image fails because image is only saved
        correctly to file system after appliction has been terminated.
        As a temporary solution, a second copy (of jpg format) of the image is stored, too.
    */
    fig->save(file_name + "_d.jpg");

    return result;
}

bool PlotExporter::ExportStatisticsPlot(const std::string file_name, const StatisticCalculation::Axes& axes)
{
    auto fig = figure(true);
    auto ax = fig->add_axes();

    ax->bar(axes.first, axes.second)->line_width(3).face_color("green");
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
    


    ax->yticks({0, 25, 50, 75, 100});
    ax->ylim({0.0, 100.00 });

    ax->font_size(32);
    //xlabel("Bins");
    //ylabel("%");

    ax->font(""); // ?
    ax->title_font_weight();
   
    /**/

    fig->size(2000, 2000);
    fig->font_size(32);

    return fig->save(file_name + ".png");
}

