#include "OptionManager.h"
#include <utility>

FOptionManager FOptionManager::Instance;

FOptionManager::FOptionManager()
{
    {
        std::vector<std::string> InputOptions({"-h"});
        FHelpOption* OptionAction = new FHelpOption(InputOptions);

        auto ExecutedOnAction = [this](){this->PrintHelp();};
        OptionAction->RegisterOnActionExcutedFunction(ExecutedOnAction);

        RegisterInputOption(InputOptions, OptionAction);
    }

    {
        std::vector<std::string> InputOptions({"-c", "-C"});
        FCategoryOption* OptionAction = new FCategoryOption(InputOptions);

        auto ExecutedOnAction = [this](std::vector<std::unique_ptr<FCategoryInfo>>& CategoryInfos)
        {
            for(auto& iter : CategoryInfos)
            {
                this->CategoryInfos.push_back(std::move(iter));
            }
        };
        OptionAction->RegisterOnActionExcutedFunction(ExecutedOnAction);

        RegisterInputOption(InputOptions, OptionAction);
    }

    {
        std::vector<std::string> InputOptions({"-s", "-S"});
        FSourceDirectoryPathOption* OptionAction = new FSourceDirectoryPathOption(InputOptions);

        auto ExecutedOnAction = [this](std::string SourceDirectoryPath){ this->SourceDirectoryPath = SourceDirectoryPath; };
        OptionAction->RegisterOnActionExcutedFunction(ExecutedOnAction);

        RegisterInputOption(InputOptions, OptionAction);
    }

    {
        std::vector<std::string> InputOptions({"-d", "-D"});
        FDestinationDirectoryPathOption* OptionAction = new FDestinationDirectoryPathOption(InputOptions);

        auto ExecutedOnAction = [this](std::string DestinationDirectoryPath){ this->DestinationDirectoryPath = DestinationDirectoryPath; };
        OptionAction->RegisterOnActionExcutedFunction(ExecutedOnAction);

        RegisterInputOption(InputOptions, OptionAction);
    }
}

FOptionManager &FOptionManager::Get()
{
    return Instance;
}

int FOptionManager::RegisterOption(int index, char* argv[])
{
    std::string Tmp = argv[index];
    std::string Option;
    Option.assign(Tmp.begin(), Tmp.end());

    return OptionActions[Option]->Action(index, argv);
}

bool FOptionManager::IsOptionSatisfactory()
{
    bool ret = true;
    for(auto iter : OptionActions)
    {
        ret |= (iter.second)->IsSatisfactory();
    }

    return ret;
}

std::string FOptionManager::GetSourceDirectoryPath()
{
    return SourceDirectoryPath;
}

std::vector<std::unique_ptr<FCategoryInfo>> &FOptionManager::GetCategoryInfos()
{
    return CategoryInfos;
}

std::string FOptionManager::GetDestinationDirectoryPath()
{
    return DestinationDirectoryPath;
}

void FOptionManager::RegisterInputOption(std::vector<std::string> InputOptions, OptionAction *OptionAction)
{
    for(auto iter : InputOptions)
    {
        OptionActions.insert(std::make_pair(iter, OptionAction));
    }
}

void FOptionManager::PrintHelp()
{
    for(auto iter : OptionActions)
    {
        iter.second->Print();
    }
}
