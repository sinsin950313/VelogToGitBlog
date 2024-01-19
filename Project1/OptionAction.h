#pragma once

#include <string>
#include <vector>
#include <functional>
#include "CategoryInfo.h"
#include <memory>

class OptionAction
{
public:
    OptionAction(std::vector<std::string> InputOptions);

public:
    virtual std::string GetDescription() = 0;

    virtual int Action(int Index, char* argv[]) = 0;

public:
    bool IsSatisfactory();

    void Print();

protected:
    void OptionSatisfied();

private:
    std::vector<std::string> InputOptions;

    bool bIsSatisfactory;
};

class FHelpOption : public OptionAction
{
public:
    FHelpOption(std::vector<std::string> InputOptions);

    virtual int Action(int Index, char* argv[]) override;

    virtual std::string GetDescription() override;

public:
    void RegisterOnActionExcutedFunction(std::function<void(void)> Func);

private:
    std::function<void(void)> OnAction;
};

class FCategoryOption : public OptionAction
{
public:
    FCategoryOption(std::vector<std::string> InputOptions);

    virtual int Action(int Index, char* argv[]) override;

    virtual std::string GetDescription() override;

public:
    void RegisterOnActionExcutedFunction(std::function<void(std::vector<std::unique_ptr<FCategoryInfo>>&)> Func);

private:
    void ParsingCategoryFile(std::string FilePath, std::vector<std::unique_ptr<FCategoryInfo>>& CategoryInfos);

    void ParsingCategory(std::string& Content, std::vector<std::unique_ptr<FCategoryInfo>>& CategoryInfos, int Index = 0);

    int ParsingTag(std::unique_ptr<FCategoryInfo>& CategoryInfo, std::string& Content, std::vector<std::unique_ptr<FCategoryInfo>>& CategoryInfos, std::string Category, int BeginIndex);

private:
    std::function<void(std::vector<std::unique_ptr<FCategoryInfo>>&)> OnAction;
};

class FSourceDirectoryPathOption : public OptionAction
{
public:
    FSourceDirectoryPathOption(std::vector<std::string> InputOptions);

    virtual int Action(int Index, char* argv[]) override;

    virtual std::string GetDescription() override;

public:
    void RegisterOnActionExcutedFunction(std::function<void(std::string)> Func);

private:
    bool bIsSatisfactory;

    std::function<void(std::string)> OnAction;
};

class FDestinationDirectoryPathOption : public OptionAction
{
public:
    FDestinationDirectoryPathOption(std::vector<std::string> InputOptions);

    virtual int Action(int Index, char* argv[]) override;

    virtual std::string GetDescription() override;

public:
    void RegisterOnActionExcutedFunction(std::function<void(std::string)> Func);

private:
    std::function<void(std::string)> OnAction;
};