cmake_minimum_required(VERSION 3.16)
PROJECT(sDriveScrape VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()
add_executable(sDriveScraper
        sDriveScrape.cpp
        SDriveScraperWindow.cpp
        SearchSpecification.cpp
)
target_include_directories(sDriveScraper PUBLIC C:/Qt/6.10.1/mingw_64/include)
target_include_directories(sDriveScraper PUBLIC C:/Qt/6.10.1/mingw_64/bin)
target_include_directories(sDriveScraper PUBLIC C:/Qt/6.10.1/mingw_64/lib)



target_link_libraries(sDriveScraper PUBLIC Qt6::Core Qt6::Widgets )