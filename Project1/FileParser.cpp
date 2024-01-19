#include "FileParser.h"
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>

FFileParser::FFileParser(std::vector<std::unique_ptr<FCategoryInfo>> &CategoryInfos)
{
    for(auto& Info : CategoryInfos)
    {
        std::string Category = Info.get()->Key;
        std::vector<std::string> Tags = Info.get()->Values;
        for(auto Tag : Tags)
        {
            TagToCategoryMap.insert(std::make_pair(Tag, Category));
        }
    }
}

void FFileParser::Parsing(std::string DirectoryPath, std::string FileName, std::unique_ptr<FParsedFileData>& ParsedFileData)
{
    std::ifstream In(DirectoryPath + FileName, std::ios_base::binary);

    if(In.is_open())
    {
        In.seekg(0, std::ios_base::end);
        int Size = In.tellg();
        In.seekg(0, std::ios_base::beg);

        std::unique_ptr<char> pChar(new char[Size]);
        In.read(pChar.get(), Size);

        std::string Origin(pChar.get());

        ParsedFileData.get()->FileName = FileName;

        std::filesystem::path Path(FileName);
        ParsedFileData.get()->Title = Path.stem().string();

        ParsedFileData.get()->GeneratedDate = ParsingGeneratedDate(Origin);

        std::string TagBlock = ParsingTagBlock(Origin);
        std::vector<std::string> Tags = ParsingTags(TagBlock);
        ParsedFileData.get()->Category = FindCategory(Tags);
        ParsedFileData.get()->Tags = Tags;

        ParsedFileData.get()->Content = ParsingContent(Origin, Size);

        ParsedFileData.get()->bHasUnDefined = CheckUndefined(Origin);

        PrintPreview(ParsedFileData);
    }

    In.close();
}

std::string FFileParser::ParsingGeneratedDate(std::string& Content)
{
    std::string Key = "date: ";
    std::string::size_type n = Content.find(Key);
    std::string GeneratedDate = Content.substr(n + Key.size(), 10);

    return GeneratedDate;
}

bool FFileParser::CheckUndefined(std::string& Content)
{
    return Content.find("undefined") != std::string::npos;
}

std::string FFileParser::ParsingTagBlock(std::string& Content)
{
    std::string Key = "tags: ";
    std::string::size_type TagPosition = Content.find(Key);

    std::string Begin = "[";
    std::string End = "]";

    std::string::size_type BeginIndex = Content.find(Begin, TagPosition);
    std::string::size_type EndIndex = Content.find(End, TagPosition);

    return Content.substr(BeginIndex + Begin.size(), EndIndex - End.size());
}

std::vector<std::string> FFileParser::ParsingTags(std::string& Content)
{
    std::vector<std::string> Tags;

    std::string Tag;
    bool bIsStarted = false;
    for(int i = 0; i < Content.size(); ++i)
    {
        if(Content[i] == '\"')
        {
            if(bIsStarted)
            {
                Tags.push_back(Tag);
                Tag.clear();
            }
            bIsStarted = !bIsStarted;
        }
        else
        {
            if(bIsStarted)
            {
                Tag += Content[i];
            }
        }
    }

    return Tags;
}

std::string FFileParser::FindCategory(std::vector<std::string>& Tags)
{
    for(auto Tag : Tags)
    {
        if(TagToCategoryMap.find(Tag) != TagToCategoryMap.end())
        {
            return TagToCategoryMap[Tag];
        }
    }

    std::string DefaultTag = "...";
    std::string DefaultCategory = "Non";
    return TagToCategoryMap.find(DefaultTag) != TagToCategoryMap.end() ? TagToCategoryMap[DefaultTag] : DefaultCategory;
}

std::string FFileParser::ParsingContent(std::string &Content, int MaximumSize)
{
    std::string Key = "---\n";

    std::string::size_type Tmp = Content.find(Key);
    std::string::size_type Pos = Content.find(Key, Tmp + Key.size());

    int LastPos = Pos + Key.size();
    return Content.substr(LastPos, MaximumSize - LastPos);
}

void FFileParser::PrintPreview(std::unique_ptr<FParsedFileData> &ParsedData)
{
    std::cout << std::endl;
    std::cout << "----------------------- Parsed Post -----------------------" << std::endl;
    std::cout << "Generated Date : " << ParsedData.get()->GeneratedDate << std::endl;
    std::cout << "Title : " << ParsedData.get()->Title << std::endl;
    std::cout << "Category : " << ParsedData.get()->Category << std::endl;
    std::cout << "Has Undefined : " << std::boolalpha << ParsedData.get()->bHasUnDefined << std::noboolalpha << std::endl;
    std::cout << "Content" << std::endl << ParsedData.get()->Content.substr(0, 200) + "\n\n" << std::endl;
}
