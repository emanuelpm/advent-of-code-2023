#include "AdventOfCode2023.h"
#include "Utilities.h"

#include <cassert>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>


namespace AdventOfCode2023
{
    void Day03(const std::string_view inFile)
    {
        struct SchematicSlot
        {
            uint16_t value = 0;

            enum Type : uint8_t
            {
                Empty,
                Value,
                Gear
            };

            Type type = Empty;
            uint8_t adjacent_count = 0;
        };

        std::vector<std::vector<SchematicSlot>> schematic;
        int32_t cur_line = 0;
        Utilities::ReadFileByLine(inFile, [&schematic, &cur_line](const std::string_view inLine)
        {
            auto& array = schematic.emplace_back();
            array.resize(inLine.size());

            int run_val = 0;
            int run_start = -1;
            for (int i = 0; i < inLine.size(); ++i)
            {
                const char& c = inLine[i];
                if (std::isdigit(c))
                {
                    if (run_start == -1)
                    {
                        run_start = i;
                    }

                    run_val = (run_val * 10) + (c - '0');
                }
                else
                {
                    run_val = 0;
                }
            }

            ++cur_line;
        });

        auto CheckForSymbol = [&schematic](int inLineIdx, int inCharIdx) -> bool
        {
            // Line above
            if (inLineIdx > 0)
            {
                if (inCharIdx > 0)
                {
                    if (const SchematicSlot& c = schematic[inLineIdx - 1][inCharIdx - 1]; !std::isdigit(c) && c != '.')
                    {
                        return true;
                    }
                }

                if (const SchematicSlot& c = schematic[inLineIdx - 1][inCharIdx + 0]; !std::isdigit(c) && c != '.')
                {
                    return true;
                }

                if (inCharIdx < (schematic[inLineIdx].size() - 1))
                {
                    if (const SchematicSlot& c = schematic[inLineIdx - 1][inCharIdx + 1]; !std::isdigit(c) && c != '.')
                    {
                        return true;
                    }
                }
            }

            // Current line
            if (inCharIdx > 0)
            {
                if (const SchematicSlot& c = schematic[inLineIdx + 0][inCharIdx - 1]; !std::isdigit(c) && c != '.')
                {
                    return true;
                }
            }

            if (inCharIdx < (schematic[inLineIdx].size() - 1))
            {
                if (const SchematicSlot& c = schematic[inLineIdx + 0][inCharIdx + 1]; !std::isdigit(c) && c != '.')
                {
                    return true;
                }
            }

            // Line below
            if (inLineIdx < (schematic.size() - 1))
            {
                if (inCharIdx > 0)
                {
                    if (const char& c = schematic[inLineIdx + 1][inCharIdx - 1]; !std::isdigit(c) && c != '.')
                    {
                        return true;
                    }
                }

                if (const char& c = schematic[inLineIdx + 1][inCharIdx + 0]; !std::isdigit(c) && c != '.')
                {
                    return true;
                }

                if (inCharIdx < (schematic[inLineIdx].size() - 1))
                {
                    if (const char& c = schematic[inLineIdx + 1][inCharIdx + 1]; !std::isdigit(c) && c != '.')
                    {
                        return true;
                    }
                }
            }

            return false;
        };

        int p1_sum = 0;
        int p2_sum = 0;
        for (int l = 0; l < schematic.size(); ++l)
        {
            const std::string& line = schematic[l];
                        bool bAdjacent = false;
            for (int c = 0; c < line.size(); ++c)
            {
                if (const char& v = line[c]; std::isdigit(v))
                {
                    run_val = (run_val * 10) + (v - '0');

                    if (!bAdjacent)
                    {
                        bAdjacent = CheckForSymbol(l, c);
                    }
                }
                else
                {
                    if (bAdjacent)
                    {
                        p1_sum += run_val;
                    }

                    run_val = 0;
                    bAdjacent = false;
                }
            }

            if (bAdjacent)
            {
                p1_sum += run_val;
            }

        }

        Utilities::PrintAnswer(1, p1_sum); // Expected: 527446
        Utilities::PrintAnswer(2, p2_sum); // Expected:
    }
} // AdventOfCode2023
