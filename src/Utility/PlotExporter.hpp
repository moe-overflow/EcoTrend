#pragma once

#include <string>
#include <vector>

#include "../Data/PlotData.hpp"

class PlotExporter
{
public:
    static bool ExportPlot(
            const std::string file_name,
            std::vector<double> const& x,
            std::vector<double> const& y,
            PlotLimits limits,
            const std::string color
    );

    static bool ExportStatisticsPlot(const std::string file_name, StatisticCalculation::Axes const& axes);
};
