#include "AdventOfCode2023.h"
#include "Utilities.h"

#include <cassert>


namespace AdventOfCode2023
{
    void Day01(const std::string_view inFile)
    {
        int p1_calibration_sum = 0;
        int p2_calibration_sum = 0;

        Utilities::ReadFileByLine(inFile, [&p1_calibration_sum, &p2_calibration_sum](const std::string_view inLine)
        {
            int p1_first = -1;
            int p1_last = -1;
            int p2_first = -1;
            int p2_last = -1;

            auto PossiblyUpdateFirstAndLast = [](const int inValue, int& inFirst, int& inLast)
            {
                if (inFirst == -1)
                {
                    inFirst = inValue;
                }

                inLast = inValue;
            };

            auto ParseSubstringForValues = [&PossiblyUpdateFirstAndLast](
                const std::string_view inSubstr, int& inFirst, int& inLast) -> void
            {
                // Return the leftmost and rightmost numbers, which could be the same substrings if they are the only ones

                struct SPair
                {
                    std::string::size_type pos = std::string::npos;
                    int value = -1;

                    [[nodiscard]] bool IsValid() const
                    {
                        return pos != std::string::npos && value > 0 && value < 10;
                    }
                };

                SPair left;
                SPair right;

                auto UpdatePairs = [&left, &right](const std::string_view inSubstr, const std::string_view inFind,
                                                   const int inValue)
                {
                    bool bFound = false;

                    std::string::size_type cur_pos = inSubstr.find(inFind);
                    while (cur_pos != std::string::npos)
                    {
                        if (left.pos == std::string::npos || cur_pos < left.pos)
                        {
                            left.pos = cur_pos;
                            left.value = inValue;

                            bFound = true;
                        }

                        if (right.pos == std::string::npos || cur_pos > right.pos)
                        {
                            right.pos = cur_pos;
                            right.value = inValue;

                            bFound = true;
                        }

                        cur_pos = inSubstr.find(inFind, cur_pos + 1);
                    }

                    return bFound;
                };

                // Not efficient but gets the job done
                bool bFound = UpdatePairs(inSubstr, "one", 1);
                bFound |= UpdatePairs(inSubstr, "two", 2);
                bFound |= UpdatePairs(inSubstr, "three", 3);
                bFound |= UpdatePairs(inSubstr, "four", 4);
                bFound |= UpdatePairs(inSubstr, "five", 5);
                bFound |= UpdatePairs(inSubstr, "six", 6);
                bFound |= UpdatePairs(inSubstr, "seven", 7);
                bFound |= UpdatePairs(inSubstr, "eight", 8);
                bFound |= UpdatePairs(inSubstr, "nine", 9);

                if (bFound)
                {
                    assert(left.IsValid());
                    assert(right.IsValid());

                    PossiblyUpdateFirstAndLast(left.value, inFirst, inLast);
                    PossiblyUpdateFirstAndLast(right.value, inFirst, inLast);
                }
            };

            std::string sub_string;
            for (const char& c : inLine)
            {
                if (std::isalpha(c))
                {
                    sub_string += c;
                }
                else
                {
                    if (!sub_string.empty())
                    {
                        ParseSubstringForValues(sub_string, p2_first, p2_last);
                        sub_string.clear();
                    }

                    if (std::isdigit(c))
                    {
                        const int i = c - '0';
                        PossiblyUpdateFirstAndLast(i, p1_first, p1_last);
                        PossiblyUpdateFirstAndLast(i, p2_first, p2_last);
                    }
                }
            }

            if (!sub_string.empty())
            {
                ParseSubstringForValues(sub_string, p2_first, p2_last);
            }

            assert(p1_first > -1);
            assert(p2_first > -1);

            p1_calibration_sum += (p1_first * 10) + p1_last;
            p2_calibration_sum += (p2_first * 10) + p2_last;
        });

        Utilities::PrintAnswer(1, p1_calibration_sum); // Expected: 52974
        Utilities::PrintAnswer(2, p2_calibration_sum); // Expected: 53340
    }
} // AdventOfCode2023
