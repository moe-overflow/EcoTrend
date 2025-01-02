#pragma once

#include <ctime>
#include <vector>

struct DataPoint
{
    double time;
    double value;
};

class JSON_Handler
{
public:
    static std::time_t ParseTimestamp(const std::string& iso_time);
    static std::vector<DataPoint> ReadJsonFile(const std::string& filename);
};

