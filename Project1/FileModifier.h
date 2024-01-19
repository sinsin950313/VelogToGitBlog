#pragma once

#include <string>
#include "ParsedFileData.h"
#include <memory>

class FFileModifier
{
public:
    FFileModifier(std::string FileSavingPath);

public:
    void Modify(std::unique_ptr<FParsedFileData>& ParsedFileData);

private:
    const std::string ModifiedFileDestinationPath;
};