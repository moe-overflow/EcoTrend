#pragma once

class Files
{
public:
    // Returns vector of all json files in a certain directory
    static std::vector<std::string> GetJsonFiles(const std::string& directory);

};