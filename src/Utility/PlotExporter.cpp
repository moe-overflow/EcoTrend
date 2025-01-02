#include "PlotExporter.hpp"

#include <matplot/matplot.h>

void PlotExporter::ExportPlot(const std::vector<double> &x, const std::vector<double> &y, double x_min, double x_max,
                              double y_min, double y_max) {
    using namespace matplot;

    auto fig = figure(true);
    auto ax = fig->add_axes();
    ax->plot(x, y)->line_width(2).color("blue");

    ax->xlim({ x_min, x_max });
    ax->ylim({ y_min, y_max });

    fig->size(800, 800);

    fig->save("snapshot.png");
}
