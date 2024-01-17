#pragma once

#include <string>
#include <vector>

struct FParsedFileData
{
    std::string FileName;

    std::string Title;

    std::string GeneratedDate;

    std::string Category;

    std::vector<std::string> Tags;

    std::string Content;

    bool bHasUnDefined;
};