#include <filesystem>
#include <string>
#include <vector>

#include "Files.hpp"

std::vector<std::string> Files::GetJsonFiles(std::string const& directory)
{
    std::vector<std::string> files;
    for (auto const& entry : std::filesystem::directory_iterator(directory))
        if (entry.is_regular_file() && entry.path().extension() == ".json")
            files.push_back(entry.path().string());

    return files;
}
