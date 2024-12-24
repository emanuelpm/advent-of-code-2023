cmake_minimum_required(VERSION 3.20)

project(AdventOfCode2023)

add_executable(AOC2023
        Include/AdventOfCode2023.h
        Include/Utilities.h

        Source/Main.cpp
        Source/Utilities.cpp

        Source/Day01.cpp
        Source/Day02.cpp
        Source/Day03.cpp
)

set_property(TARGET AOC2023 PROPERTY CXX_STANDARD 23)
set_property(TARGET AOC2023 PROPERTY CXX_STANDARD_REQUIRED On)
set_property(TARGET AOC2023 PROPERTY CXX_EXTENSIONS Off)

target_include_directories(AOC2023 PRIVATE Include)
