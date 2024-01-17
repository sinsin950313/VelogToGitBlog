#pragma once

#include <string>
#include <vector>
#include <map>
#include "CategoryInfo.h"
#include "OptionAction.h"
#include <memory>

class FOptionManager
{
private:
    FOptionManager();

    static FOptionManager Instance;

public:
    static FOptionManager& Get();

    int RegisterOption(int index, char* argv[]);

    bool IsOptionSatisfactory();

    std::string GetSourceDirectoryPath();

    std::vector<std::unique_ptr<FCategoryInfo>>& GetCategoryInfos();

    std::string GetDestinationDirectoryPath();

private:
    void RegisterInputOption(std::vector<std::string> InputOptions, OptionAction* OptionAction);

    void PrintHelp();

private:
    std::map<std::string, OptionAction*> OptionActions;

    std::string SourceDirectoryPath;

    std::vector<std::unique_ptr<FCategoryInfo>> CategoryInfos;

    std::string DestinationDirectoryPath;
};