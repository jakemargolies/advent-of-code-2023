cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(advent VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include_directories(../day1/include)

set(SOURCES main.cpp src/day5.cpp)

add_executable(day5 ${SOURCES})

target_include_directories(day5 PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/src"
    # "${PROJECT_SOURCE_DIR}/../day1/include"
    # "${PROJECT_SOURCE_DIR}/../day1/src"
)
