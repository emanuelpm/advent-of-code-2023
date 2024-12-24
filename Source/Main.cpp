#include "AdventOfCode2023.h"

#include <iostream>
#include <string_view>


int main(int argc, const char** const argv)
{
    if (argc != 2)
    {
        std::cerr << "Must pass in the day";
        return -1;
    }

#define IMPL_DAY(day)                                   \
    case day:                                           \
        AdventOfCode2023::Day##day("Day"#day".txt");    \
        break

    switch (const int day = std::atoi(argv[1]))
    {
    IMPL_DAY(01);
    IMPL_DAY(02);
    IMPL_DAY(03);

    default:
        std::cerr << "Invalid day passed in: " << day;
        return -2;
    }

#undef IMPL_DAY

    return 0;
}
