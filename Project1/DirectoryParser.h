#pragma once

#include <string>
#include <vector>

class FDirectoryParser
{
public:
	bool Parse(std::string Path);

	std::vector<std::string>& GetFiles();

private:
	std::vector<std::string> FilePathes;
};