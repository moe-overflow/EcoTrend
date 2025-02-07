#include <string>
#include <vector>
#include <filesystem>

#include "Files.hpp"

std::vector<std::string> Files::GetJsonFiles(const std::string& directory)
{
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(directory))
        if (entry.is_regular_file() && entry.path().extension() == ".json")
            files.push_back(entry.path().string());

    return files;
}
