#pragma once

#include <vector>
#include <string>

#include "../Data/PlotData.hpp"

class PlotExporter
{
public:
    static bool ExportPlot(
        const std::string file_name, 
        const std::vector<double>& x, 
        const std::vector<double>& y, 
        PlotLimits limits, 
        const std::string color);

    static bool ExportStatisticsPlot(const std::string file_name, const StatisticCalculation::Axes& axes);


};

