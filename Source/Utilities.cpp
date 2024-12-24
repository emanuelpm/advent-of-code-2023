#include "Utilities.h"

#include <fstream>


namespace AdventOfCode2023::Utilities {

bool ReadFileByLine(std::string_view inFile, const FileLineVisitor& inVisitor)
{
    if (inFile.empty())
    {
        return false;
    }

    if (std::ifstream in(inFile); in.is_open())
    {
        std::string line;
        while (std::getline(in, line))
        {
            inVisitor(line);
        }

        return true;
    }

    return false;
}

}
