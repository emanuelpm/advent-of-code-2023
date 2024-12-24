#pragma once

#include <string_view>


namespace AdventOfCode2023 {

#define DEF_DAY(day)    void Day##day(std::string_view inFile)

    DEF_DAY(01);
    DEF_DAY(02);
    DEF_DAY(03);

#undef DEF_DAY

} // AdventOfCode2023
