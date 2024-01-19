#include "OptionAction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

OptionAction::OptionAction(std::vector<std::string> InputOptions) : InputOptions(InputOptions)
{
}

bool OptionAction::IsSatisfactory()
{
    return bIsSatisfactory;
}

void OptionAction::Print()
{
    for(auto& iter : InputOptions)
    {
        std::cout << iter << " ";
    }
    std::cout << GetDescription() << std::endl;
}

void OptionAction::OptionSatisfied()
{
    bIsSatisfactory = false;
}

FHelpOption::FHelpOption(std::vector<std::string> InputOptions) : OptionAction(InputOptions)
{
    OptionSatisfied();
}

int FHelpOption::Action(int Index, char *argv[])
{
    OnAction();
    return Index + 1;
}

std::string FHelpOption::GetDescription()
{
    return "Help";
}

void FHelpOption::RegisterOnActionExcutedFunction(std::function<void(void)> Func)
{
    OnAction = Func;
}

FCategoryOption::FCategoryOption(std::vector<std::string> InputOptions) : OptionAction(InputOptions)
{
}

int FCategoryOption::Action(int Index, char *argv[])
{
    std::string Tmp = argv[Index + 1];
    std::string CategoryFilePath;
    CategoryFilePath.assign(Tmp.begin(), Tmp.end());

    std::vector<std::unique_ptr<FCategoryInfo>> ParsedCategoryDatas;
    ParsingCategoryFile(CategoryFilePath, ParsedCategoryDatas);

    std::cout << "Parsed Category Datas" << std::endl;
    for(auto& Data : ParsedCategoryDatas)
    {
        std::cout << "Category : " << Data.get()->Key << std::endl;
        std::cout << "\t Tag : ";
        for(auto Tag : Data.get()->Values)
        {
            std::cout << Tag << " ";
        }
        std::cout << std::endl;
    }

    OnAction(ParsedCategoryDatas);

    OptionSatisfied();

    return Index + 2;
}

std::string FCategoryOption::GetDescription()
{
    return "Category Information File Path - Content should be [Category, {Tag1, Tag2, ... , TagN}]. [Category, ...] is Default";
}

void FCategoryOption::RegisterOnActionExcutedFunction(std::function<void(std::vector<std::unique_ptr<FCategoryInfo>>&)> Func)
{
    OnAction = Func;
}

void FCategoryOption::ParsingCategoryFile(std::string FilePath, std::vector<std::unique_ptr<FCategoryInfo>>& CategoryInfos)
{
    std::ifstream In(FilePath);
    if(In.is_open())
    {
        In.seekg(0, std::ios_base::end);
        int Size = In.tellg();
        In.seekg(0, std::ios_base::beg);

        std::unique_ptr<char> pChar(new char[Size]);
        In.read(pChar.get(), Size);
        std::string Content(pChar.get());

        ParsingCategory(Content, CategoryInfos);
    }
}

void FCategoryOption::ParsingCategory(std::string &Content, std::vector<std::unique_ptr<FCategoryInfo>> &CategoryInfos, int Index)
{
    std::unique_ptr<FCategoryInfo> Info(new FCategoryInfo);

    std::string::size_type BeginIndex = Content.find("[", Index);
    std::string::size_type CategoryEndIndex = Content.find(",", Index);

    std::string Category = Content.substr(BeginIndex + 1, CategoryEndIndex - BeginIndex - 1);
    Info.get()->Key = Category;

    std::string::size_type TagBeginIndex = Content.find("{", Index);
    std::string::size_type TagEndIndex = Content.find("}", Index);

    std::string Tags = Content.substr(TagBeginIndex + 1, TagEndIndex - TagBeginIndex - 1);
    int TagIndex = 0;
    while(TagIndex < Tags.size())
    {
        TagIndex = ParsingTag(Info, Tags, CategoryInfos, Category, TagIndex);
    }
    CategoryInfos.push_back(std::move(Info));

    std::string::size_type EndIndex = Content.find("]", Index);
    if(Content.find("[", EndIndex) != std::string::npos)
    {
        ParsingCategory(Content, CategoryInfos, EndIndex + 1);
    }
}

int FCategoryOption::ParsingTag(std::unique_ptr<FCategoryInfo>& CategoryInfo, std::string& Content, std::vector<std::unique_ptr<FCategoryInfo>> &CategoryInfos, std::string Category, int BeginIndex)
{
    if(Content[BeginIndex] == ' ')
    {
        BeginIndex += 1;
    }

    std::string::size_type EndIndex = Content.find(",", BeginIndex);

    std::string Tag;
    if (EndIndex == std::string::npos)
    {
        Tag = Content.substr(BeginIndex, Content.size());
        EndIndex = Content.size();
    }
    else
    {
        Tag = Content.substr(BeginIndex, EndIndex);
    }
    CategoryInfo.get()->Values.push_back(Tag);

    return EndIndex + 1;
}

FSourceDirectoryPathOption::FSourceDirectoryPathOption(std::vector<std::string> InputOptions) : OptionAction(InputOptions), bIsSatisfactory(false)
{
}

int FSourceDirectoryPathOption::Action(int Index, char *argv[])
{
    std::filesystem::path Path(argv[Index + 1]);
    if(std::filesystem::is_directory(Path))
    {
        std::cout << std::endl;
        std::cout << "Source Directory Path : " << Path << std::endl;
        std::cout << std::endl;

        OnAction(Path.string());

        OptionSatisfied();
    }
    else
    {
        std::cout << Path << " is not Directory" << std::endl;
    }

    return Index + 2;
}

std::string FSourceDirectoryPathOption::GetDescription()
{
    return "Source Posting Files Directory";
}

void FSourceDirectoryPathOption::RegisterOnActionExcutedFunction(std::function<void(std::string)> Func)
{
    OnAction = Func;
}

FDestinationDirectoryPathOption::FDestinationDirectoryPathOption(std::vector<std::string> InputOptions) : OptionAction(InputOptions)
{
}

int FDestinationDirectoryPathOption::Action(int Index, char *argv[])
{
    std::filesystem::path Path(argv[Index + 1]);

    if(std::filesystem::is_directory(Path))
    {
        std::cout << std::endl;
        std::cout << "Destination Directory Path : " << Path << std::endl;
        std::cout << std::endl;

        OnAction(Path.string());

        OptionSatisfied();
    }
    else
    {
        std::cout << Path << " is not Directory" << std::endl;
    }

    return Index + 2;
}

std::string FDestinationDirectoryPathOption::GetDescription()
{
    return "Modifed File Destination Directory";
}

void FDestinationDirectoryPathOption::RegisterOnActionExcutedFunction(std::function<void(std::string)> Func)
{
    OnAction = Func;
}
