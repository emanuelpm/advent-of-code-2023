#pragma once

#include <functional>
#include <iostream>
#include <string_view>


namespace AdventOfCode2023::Utilities {

using FileLineVisitor = std::function<void(std::string_view)>;

bool ReadFileByLine(std::string_view inFile, const FileLineVisitor& inVisitor);

template<typename T>
void PrintAnswer(int inPart, T inAnswer)
{
    using namespace std;
    cout << "[Part " << inPart << "] " << inAnswer << endl;
}

} // AdventOfCode2023::Utilities
