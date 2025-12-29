#pragma once

#include <deque>
#include <map>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <vector>
#include <filesystem>
#include <__msvc_filebuf.hpp>

namespace fs = std::filesystem;

namespace dirtype{
    enum DirType
    {
        null,
        OutlierDir,
        CourseDir,
        TermDir,
        WeekDir,
        StudentDir
    };
}

std::vector<std::string> outlierSubstring = {
    "_Previous Blocks"
};

std::vector<std::string> courseSubstring = {
    "DAVE_",
    "GAME_"
};

std::vector<std::string> termSubstring = {
    "2024",
    "2025"
};

std::vector<std::string> weekSubstring = {
    "Week"
};

std::vector<std::string> studentSubstring = {
    "ruiz"
};


std::map<DirType, std::vector<std::string>> dirTypePredicates = {
    {dirtype::OutlierDir, outlierSubstring},
    {dirtype::CourseDir, courseSubstring},
    {dirtype::TermDir, termSubstring},
    {dirtype::WeekDir, weekSubstring},
    {dirtype::StudentDir, studentSubstring}
};

std::string toLower(std::string input){
    std::transform(
        input.begin(),
        input.end(),
        input.begin(),
        [](char c){return std::tolower(c);});
    return input;
}

dirtype::DirType get_directory_type(fs::path filepath){
    std::string stem = toLower((filepath.stem().string()));
    dirtype::DirType resultType = dirtype::null;
    for (auto item = dirTypePredicates.begin(); item != dirTypePredicates.end(); item++){
        auto dirType = item->first;
        std::vector<std::string> substrings = item->second;
        for (std::string str : substrings){
            str = toLower(str);
            if (stem.find(str) != std::string::npos){
                resultType = dirType;
                break;
            };
        };
    };
    
    dirtype::DirType parentDirType = get_directory_type(filepath.parent_path().string()); // TODO: this is recursive make it not
    if (parentDirType == dirtype::WeekDir)
    {
        std::vector<fs::path> matches = filteredBreadthFirstSearch(filepath);
        if (matches.size() > 0)
        {
            resultType = dirtype::OutlierDir;
        }
    }
    return resultType;
};

std::vector<fs::path>* filteredBreadthFirstSearch(std::string rootDirectory, int depth=-1)
{
    fs::path rootPath = rootDirectory;
    std::vector<fs::path>* matches = new std::vector<fs::path>;
    std::deque<fs::path>* _deque = new std::deque<fs::path>;
    _deque->push_back(rootPath);

    int currentDepth = 0;
    int cachedChildCount = 0;
    int iterationOnLevel = 0;
    while (_deque->size() > 0 && currentDepth != depth)
    {
        fs::path currentPath = _deque->pop_front();
        std::vector<fs::path> dirContent;
        fs::directory_iterator currentIter(currentPath);
        std::transform(
            fs::begin(currentIter), fs::end(currentIter),
            std::back_inserter(dirContent),
            [_deque](fs::path p, std::deque<fs::path>*& _deque)
            {
                // TODO: finish transfering dirtype resolution from python proto -- test for print diriter may
                // return stems. Also fix recursion in dirtype func first!
                dirtype::DirType dirType = get_directory_type(p);
                
                return p;
            }
            );
    };
    printf("Filtered Breadth First Search\n");
    return matches;
};


int main(int argc, char* argv[])
{
    filteredBreadthFirstSearch(R"(S:\Academics\Courses)");
    return 0;
};

    
