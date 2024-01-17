#include <string>
#include <vector>
#include <memory>

#include "DirectoryParser.h"
#include "FileParser.h"
#include "ParsedFileData.h"
#include "FileModifier.h"
#include "OptionManager.h"

#include <locale>
#include <iostream>

int main(int argc, char* argv[])
{
	// UTF-8을 사용하기 위해 로캘 및 코드 컨버터 설정
    std::locale::global(std::locale(".utf8")); // 로캘 설정

	for (int i = 1; i < argc;)
	{
		i = FOptionManager::Get().RegisterOption(i, argv);
	}

	if (FOptionManager::Get().IsOptionSatisfactory())
	{
		FDirectoryParser DirectoryParser;
		if (!DirectoryParser.Parse(FOptionManager::Get().GetSourceDirectoryPath()))
		{
			return 0;
		}

		std::vector<std::string> &FileNames = DirectoryParser.GetFiles();

		FFileParser FileParser(FOptionManager::Get().GetCategoryInfos());
		std::vector<std::unique_ptr<FParsedFileData>> ParsedFileDataList;
		for (auto& FileName : FileNames)
		{
			std::unique_ptr<FParsedFileData> ParsedFileData(new FParsedFileData);
			FileParser.Parsing(FOptionManager::Get().GetSourceDirectoryPath(), FileName, ParsedFileData);
			ParsedFileDataList.push_back(std::move(ParsedFileData));
		}

		FFileModifier FileModifier(FOptionManager::Get().GetDestinationDirectoryPath());
		for (auto &FileData : ParsedFileDataList)
		{
			FileModifier.Modify(FileData);
		}
	}

	return 0;
}