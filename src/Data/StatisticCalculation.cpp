#include "StatisticCalculation.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>


Statistics StatisticCalculation::CalculateStatistics(
        std::vector<double> const& values,
        PredefinedStatisticsValues const& predefined
)
{

    Statistics statistics{};

    statistics.Nominal = predefined.Nominal;
    statistics.LSL = predefined.LSL;
    statistics.USL = predefined.USL;

    /**/

    auto const size = values.size();

    // Mean value
    auto const mean = std::accumulate(values.begin(), values.end(), 0.0) / values.size();
    statistics.Mean = mean;

    // STD deviation
    statistics.STD_Deviation = std::sqrt(
            std::accumulate(
                    values.begin(),
                    values.end(),
                    0.0,
                    [&mean](double acc, double value) { return acc + std::pow((value - mean), 2); }
            )
            / size
    );

    // Min & Max
    statistics.MaxValue = *std::max_element(values.begin(), values.end());
    statistics.MinValue = *std::min_element(values.begin(), values.end());

    // Below LSL and Above USL
    {
        int count_below_lsl{ 0 };
        int count_above_usl{ 0 };

        for (auto value : values)
        {
            if (value < predefined.LSL)
                count_below_lsl++;
            if (value > predefined.USL)
                count_above_usl++;
        }
        statistics.BelowLSL = (count_below_lsl / values.size()) * 100;
        statistics.AboveUSL = (count_above_usl / values.size()) * 100;
    }

    // CPK
    {
        // Formula originates from https://www.toppr.com/guides/maths-formulas/cpk-formulas/

        statistics.CP = (predefined.USL - predefined.LSL) / (6 * statistics.STD_Deviation);

        statistics.CPK = std::min(
                (predefined.USL - mean) / 3 * statistics.STD_Deviation,
                (mean - predefined.LSL) / 3 * statistics.STD_Deviation
        );
    }

    return statistics;
}

StatisticCalculation::Axes
StatisticCalculation::DetermineAxes(Statistics const& statistics, std::vector<double> const& values)
{
    std::array<uint64_t, STEP_SIZE + 1> frequency{};


    std::array<double, STEP_SIZE + 1> steps{};
    std::array<double, STEP_SIZE + 1> frequency_percentage{};

    auto const offset = (statistics.USL - statistics.LSL) / STEP_SIZE;
    for (size_t i = 0; i < STEP_SIZE + 1; i++)
    {
        frequency[i] = 0;
        frequency_percentage[i] = 0.0;
        steps[i] = statistics.LSL + offset * i;
    }

    // Verteilung/Häufigkeit der Werte
    for (auto const value : values)
    {
        for (size_t i = 0; i < STEP_SIZE + 1; i++)
        {
            if (value >= steps[i] && value < steps[i + 1])
            {
                frequency[i]++;
                break;
            }
        }
    }

    // Verteilung in %
    for (size_t i = 0; i < STEP_SIZE + 1; i++)
    {
        frequency_percentage[i] = (static_cast<double>(frequency[i]) / values.size()) * 100;
    }

    return std::make_pair(steps, frequency_percentage);
}
