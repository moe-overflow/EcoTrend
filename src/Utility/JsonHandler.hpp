#pragma once

#include <ctime>
#include <string>

#include <nlohmann/json.hpp>

struct DataPoint
{
    double time;
    double value;
};

class JSON_Handler
{
public:
    static std::time_t ParseTimestamp(std::string const& iso_time);
    //static std::vector<DataPoint> ReadJsonFile(const std::string& filename);

    static nlohmann::json ReadJsonFile(std::string const& filename);

    static void WriteJsonFile(nlohmann::json j, std::string const& destination);
};
