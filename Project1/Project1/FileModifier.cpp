#include "FileModifier.h"
#include <fstream>
#include <algorithm>

FFileModifier::FFileModifier(std::string FileSavingPath) : ModifiedFileDestinationPath(FileSavingPath)
{
}

void FFileModifier::Modify(std::unique_ptr<FParsedFileData> &ParsedFileData)
{
    std::string FileName = ParsedFileData.get()->GeneratedDate + "-" + ParsedFileData.get()->FileName;
    std::ofstream Out(ModifiedFileDestinationPath + FileName, std::ios_base::binary);
    Out.imbue(std::locale());

    if(Out.is_open())
    {
        std::string FrontMatterKey = "---\n";

        std::string FinalContent;
        FinalContent += FrontMatterKey;
        FinalContent += (std::string)"title: " + "\"" + ParsedFileData.get()->Title + "\"" +"\n";
        FinalContent += "date: " + ParsedFileData.get()->GeneratedDate + "\n";

        FinalContent += (std::string)"categories: " + "[" + "\"Development\", "+ "\"" + ParsedFileData.get()->Category + "\"" + "]" + "\n";

        FinalContent += (std::string)"tags: " + "[";
        std::vector<std::string> &Tags = ParsedFileData.get()->Tags;
        int TagSizeExceptLastOne = Tags.size() - 1;
        for (int i = 0; i < TagSizeExceptLastOne; ++i)
        {
            std::transform(Tags[i].begin(), Tags[i].end(), Tags[i].begin(), tolower);
            FinalContent += (std::string) "\"" + Tags[i] + "\"" + ", ";
        }

        if (TagSizeExceptLastOne >= 0)
        {
            std::transform(Tags[TagSizeExceptLastOne].begin(), Tags[TagSizeExceptLastOne].end(), Tags[TagSizeExceptLastOne].begin(), tolower);
            FinalContent += "\"" + Tags[TagSizeExceptLastOne] + "\"";
        }
        FinalContent += (std::string)"]" + "\n";
        FinalContent += FrontMatterKey;

        FinalContent += ParsedFileData.get()->Content;

        Out.write(FinalContent.c_str(), FinalContent.size());

        if(ParsedFileData.get()->bHasUnDefined)
        {
            std::ofstream UnDefinedLog(ModifiedFileDestinationPath + "UnDefined Log List.txt", std::ios_base::app);
            UnDefinedLog.write(FileName.c_str(), FileName.size());
            UnDefinedLog.write("\n", 1);
        }
    }
}
