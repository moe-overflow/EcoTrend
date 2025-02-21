#include "../Utility/JsonHandler.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


using namespace nlohmann;

std::time_t JSON_Handler::ParseTimestamp(std::string const& iso_time)
{
    std::tm tm = {};
    std::istringstream ss(iso_time);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
    return std::mktime(&tm);
}

json JSON_Handler::ReadJsonFile(std::string const& filename)
{
    std::ifstream file(filename);
    if (file.fail())
    {
        // todo: verify
        std::cerr << "Could not open JSON file: " << filename << std::endl;
        return {};
    }

    json j;
    file >> j;

    return j;
}
