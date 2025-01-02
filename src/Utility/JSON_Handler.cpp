#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
#include "JSON_Handler.hpp"

#include <nlohmann/json.hpp>
using namespace nlohmann;

std::time_t JSON_Handler::ParseTimestamp(const std::string& iso_time)
{
    std::tm tm = {};
    std::istringstream ss(iso_time);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
    return std::mktime(&tm);
}

std::vector<DataPoint> JSON_Handler::ReadJsonFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open JSON file: " + filename);

    json j;
    file >> j;

    std::vector<DataPoint> data_points;
    for (const auto& entry : j)
    {
        DataPoint point{};
        point.time = ParseTimestamp(entry["_time"]);
        point.value = std::stod(entry["_value"].get<std::string>());
        data_points.push_back(point);
    }

    return data_points;
}