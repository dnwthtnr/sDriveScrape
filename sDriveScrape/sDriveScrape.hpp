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
#include <QtWidgets/QtWidgets>
#include "SearchSpecification.h"
#include "SDriveScraperWindow.h"
#include <QtCore/QtDebug>

#include <QtCore/QtCore>
#include <QtCore/QFile>
#include <QtCore/QTextStream>


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
namespace sDriveScrape {
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

    std::vector<fs::path>* filteredBreadthFirstSearch(const fs::path &rootDirectory, int depth=-1);

    fs::path copyFile(fs::path src, fs::path dest, std::function<void(fs::path)> callback);

    inline int CopyOperationCount = 0;
    inline int CurrentCopyCount = 0;
    void setCopyOperationCount(int count);
    void logCopyProgress(fs::path path);


    bool copyFilePathsFromRelativeStart(std::vector<fs::path> *paths, fs::path relativeStartPath, fs::path relativeEndPath);
}

class SDriveScraperController : public QObject {
    Q_OBJECT
public:
    SDriveScraperController();
    ~SDriveScraperController() override;
    void testMsg(std::string msg);

    signals:
    void progress_updated(int current, int total);
    void search_completed();
    void copy_completed();

    public slots:
    static void start_async_search(std::shared_ptr<SearchSpecification> spec);

    
private:
    std::shared_ptr<SearchSpecification> search_spec_;
    
};

void message_handler(QtMsgType type, const QMessageLogContext &, const QString & msg);
int main(int argc, char* argv[]);

    
