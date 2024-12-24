#include "AdventOfCode2023.h"
#include "Utilities.h"

#include <cassert>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>


namespace AdventOfCode2023
{
    void Day02(const std::string_view inFile)
    {
        struct SPair
        {
            SPair(const char* inStr, int inCount)
                : color(inStr)
                , count(inCount)
            {
            }

            std::string_view color;
            int count;
            int min_needed = 0;
        };

        const std::vector<SPair> contents{{"red", 12}, {"green", 13}, {"blue", 14}};
        int p1_sum = 0;
        int p2_sum = 0;

        int line_number = 0;
        Utilities::ReadFileByLine(inFile, [&line_number, &contents, &p1_sum, &p2_sum](const std::string_view inLine)
        {
            // We are going to not parse the game number since it matches the line number :)
            ++line_number;

            auto local_contents = contents;

            // Jump past the colon and space
            const auto colon_pos = inLine.find(": ");
            assert(colon_pos >= 6);

            using std::operator""sv;

            // Now split into the games
            for (const auto game : std::views::split(inLine.substr(colon_pos + 2), "; "sv))
            {
                // Split on each set of blocks
                for (const auto block : std::views::split(game, ", "sv))
                {
                    // Get the color and amount
                    auto tokens = std::views::split(block, " "sv).begin();
                    const auto value = std::string_view(*(tokens++));
                    const auto name = std::string_view(*(tokens++));

                    for (auto& pair : local_contents)
                    {
                        if (pair.color == name)
                        {
                            const int val = std::atoi(std::string(value).c_str());
                            pair.min_needed = std::max(pair.min_needed, val);
                            if (pair.count < val)
                            {
                                break;
                            }
                        }
                    }
                }
            }

            p1_sum += line_number;
            p2_sum += [&local_contents]()
            {
                int prod = 1;
                for (const auto& item : local_contents)
                {
                    prod *= item.min_needed;
                }

                return prod;
            }();
        });

        Utilities::PrintAnswer(1, p1_sum); // Expected: 2317
        Utilities::PrintAnswer(2, p2_sum); // Expected: 74804
    }
} // namespace AdventOfCode2023
