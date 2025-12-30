#include "sDriveScrape.hpp"

#include <iostream>

void populateSubstrings()
{
    outlierSubstring->push_back("_Previous Blocks");
    courseSubstring->push_back("DAVE_");
    courseSubstring->push_back("GAME_");
    
    termSubstring->push_back("2024");
    termSubstring->push_back("2025");
    weekSubstring->push_back("week");
    studentSubstring->push_back("ruiz");
}


std::string toLower(std::string input){
    std::transform(
        input.begin(),
        input.end(),
        input.begin(),
        [](char c){return std::tolower(c);});
    return input;
}

dirtype::DirType get_directory_type(fs::path filepath, bool peekWeekSubdirs){
    // TODO: big try catch to account for non ansi characters in some file names
    try{
    std::string stem = filepath.stem().string();
    stem = toLower(filepath.stem().string());
    dirtype::DirType resultType = dirtype::null;
    for (auto const& item : dirTypePredicates){
        auto dirType = item.first;
        for (std::string str : *item.second){
            str = toLower(str);
            if (stem.find(str) != std::string::npos){
                resultType = dirType;
                break;
            };
        };
        
    };
    if (!peekWeekSubdirs || !is_directory(filepath)){
        return resultType;
    }
    
    dirtype::DirType parentDirType = get_directory_type(filepath.parent_path().string(), false);
    if (parentDirType == dirtype::WeekDir)
    {
        std::vector<fs::path>* matches = filteredBreadthFirstSearch(filepath.string(), 2);
        if (matches->size() > 0)
        {
            resultType = dirtype::OutlierDir;
        }
        free (matches);
    }
    return resultType;
    }
    catch (std::exception& e){
        std::cerr << e.what() << std::endl;
        return dirtype::null;
    }
};

std::vector<fs::path>* filteredBreadthFirstSearch(std::string rootDirectory, int depth)
{
    fs::path rootPath = rootDirectory;
    std::vector<fs::path>* matches = new std::vector<fs::path>;
    std::deque<fs::path> deque = {rootPath};

    int currentDepth = 0;
    int cachedChildCount = 0;
    int currentLevelChildCount = 0;
    int iterationOnLevel = 0;
    while (deque.size() > 0 && currentDepth != depth)
    {
        fs::path currentPath = deque.front();
        deque.pop_front();
        
        std::vector<fs::path> dirContent;
        fs::directory_iterator currentIter(currentPath);
        //currentLevelChildCount += std::distance(begin(currentIter), end(currentIter));
        for (fs::path currentDir : currentIter){
            currentLevelChildCount++;
            dirtype::DirType _dirtype = get_directory_type(currentDir);
            if (!is_directory(currentDir)){
                if (_dirtype == dirtype::StudentDir){
                    matches->push_back(currentDir);
                };
                continue;
            };

            if (_dirtype == dirtype::null){
                continue;
            };
            if (_dirtype == dirtype::StudentDir){
              matches->push_back(currentDir);
                continue;
            };
            deque.push_back(currentDir);
            //printf(currentDir.string().c_str());
            //std::cout << currentDepth << iterationOnLevel << cachedChildCount << currentLevelChildCount << currentDir << std::endl;
        };
        iterationOnLevel++;
        if (iterationOnLevel == cachedChildCount){
            //std::cout << currentDepth << iterationOnLevel << cachedChildCount << currentLevelChildCount << std::endl;
            currentDepth++;
            iterationOnLevel = 0;
            cachedChildCount = currentLevelChildCount;
            currentLevelChildCount = 0;
        };
    };
    return matches;
};


int main(int argc, char* argv[])
{
    populateSubstrings();
    std::vector<fs::path>* matches = filteredBreadthFirstSearch(R"(S:\Academics\Courses)");
    printf("%zu", matches->size());
    auto printResults = [matches] (std::vector<fs::path>* matches){
        for (auto m : *matches)
        {
            std::cout << m.string() << std::endl;
        }
    };
    printResults(matches);
    return 0;
};

    
