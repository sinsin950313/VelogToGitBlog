#include "DirectoryParser.h"
#include <filesystem>

bool FDirectoryParser::Parse(std::string Path)
{
    std::filesystem::path DirectoryPath = Path;
    if(!std::filesystem::exists(DirectoryPath))
    {
        return false;
    }

    std::filesystem::directory_iterator iter(DirectoryPath);
    while(iter != std::filesystem::end(iter))
    {
        const std::filesystem::directory_entry& entry = *iter;
        FilePathes.push_back(entry.path().filename().string());
        ++iter;
    }

    return true;
}

std::vector<std::string>& FDirectoryParser::GetFiles()
{
    return FilePathes;
}
