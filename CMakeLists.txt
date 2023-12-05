cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(advent VERSION 1.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(previous_days/day1/include)

set(SOURCES main.cpp ${PROJECT_SOURCE_DIR}/src/day2.cpp ${PROJECT_SOURCE_DIR}/previous_days/day1/src/day1.cpp)

add_executable(advent ${SOURCES})

target_include_directories(advent PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/previous_days/day1/include"
    "${PROJECT_SOURCE_DIR}/previous_days/day1/src"
)
