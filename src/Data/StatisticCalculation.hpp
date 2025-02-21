#pragma once

#include <vector>

// todo: These values should be queried from database / measurement
struct PredefinedStatisticsValues
{
    double Nominal, LSL, USL;
};

struct Statistics
{
    double Nominal, LSL, USL;
    /**/

    double Mean, STD_Deviation, MinValue, MaxValue;
    int BelowLSL, AboveUSL;
    double CP, CPK;
};

class StatisticCalculation
{
public:

    constexpr static size_t STEP_SIZE = 20;
    using Axis = std::array<double, STEP_SIZE + 1>;
    using Axes = std::pair<Axis, Axis>;

    static Statistics CalculateStatistics(const std::vector<double>& values, const PredefinedStatisticsValues& predefined);

    static Axes DetermineAxes(const Statistics& statistics, const std::vector<double>& values);


};

