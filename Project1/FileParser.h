#pragma once

#include <string>
#include "ParsedFileData.h"
#include <memory>
#include "CategoryInfo.h"
#include <vector>
#include <map>

class FFileParser
{
public:
    FFileParser(std::vector<std::unique_ptr<FCategoryInfo>>& CategoryInfos);

public:
    void Parsing(std::string DirectoryPath, std::string FileName, std::unique_ptr<FParsedFileData>& ParsedFileData);

private:
    std::string ParsingGeneratedDate(std::string& Content);

    bool CheckUndefined(std::string& Content);

    std::string ParsingTagBlock(std::string& Content);

    std::vector<std::string> ParsingTags(std::string& Content);

    std::string FindCategory(std::vector<std::string>& Tags);

    std::string ParsingContent(std::string& Content, int MaximumSize);

    void PrintPreview(std::unique_ptr<FParsedFileData>& ParsedData);

private:
    std::map<std::string, std::string> TagToCategoryMap;
};