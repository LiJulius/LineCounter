cmake_minimum_required(VERSION 3.5)
project(LineCounter)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    main.cpp
    line_counter/LineCounter.cpp
    configuration/Configuration.cpp
)

add_executable(LineCounter ${SOURCES})