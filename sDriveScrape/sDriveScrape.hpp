#pragma once

#include <deque>
#include <map>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <vector>
#include <filesystem>
#include <iterator>
#include <future>
#include <iostream>
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

inline std::vector<std::string>* outlierSubstring = new std::vector<std::string>();
inline std::vector<std::string>* courseSubstring = new std::vector<std::string>();
inline std::vector<std::string>* termSubstring = new std::vector<std::string>();
inline std::vector<std::string>* weekSubstring = new std::vector<std::string>();
inline std::vector<std::string>* studentSubstring = new std::vector<std::string>();
inline std::map<dirtype::DirType, std::vector<std::string>*>  dirTypePredicates = {
    {dirtype::OutlierDir, outlierSubstring},
    {dirtype::CourseDir, courseSubstring},
    {dirtype::TermDir, termSubstring},
    {dirtype::WeekDir, weekSubstring},
    {dirtype::StudentDir, studentSubstring}
};


void populateSubstrings();

std::string toLower(std::string input);

dirtype::DirType get_directory_type(fs::path filepath, bool peekWeekSubdirs=true);

std::vector<fs::path>* filteredBreadthFirstSearch(std::string rootDirectory, int depth=-1);

fs::path copyFile(fs::path src, fs::path dest, std::function<void(fs::path)> callback);

inline int CopyOperationCount = 0;
inline int CurrentCopyCount = 0;
void setCopyOperationCount(int count);
void logCopyProgress(fs::path path);


bool copyFilePathsFromRelativeStart(std::vector<fs::path> *paths, fs::path relativeStartPath, fs::path relativeEndPath);

int main(int argc, char* argv[]);

    
