#pragma once

#include <array>
#include <nlohmann/json.hpp>

#include "StatisticCalculation.hpp"

struct PlotLimits
{
	double x_min, x_max;
	double y_min, y_max;

};

struct PlotData
{
	std::string _ImagePath;
	std::vector<double> _Values;
	std::vector<double> _Timestamps;
	PlotLimits _PlotLimits;
	Statistics _Statistics;
};

