#pragma once

#include <vector>

class PlotExporter
{
public:
    static void ExportPlot(const std::vector<double>& x, const std::vector<double>& y,
        double x_min, double x_max, double y_min, double y_max);
};

