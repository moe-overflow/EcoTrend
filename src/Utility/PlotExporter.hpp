#pragma once

#include <string>
#include <vector>

#include "../Data/PlotData.hpp"

class PlotExporter
{
    using Dataset = std::pair<std::vector<double>, std::vector<double>>;

public:
    static bool ExportPlot(std::string const& file_name, Dataset const& dataset, PlotLimits const& limits);

    static bool ExportStatisticsPlot(std::string const& file_name, StatisticCalculation::Axes const& axes);
};
