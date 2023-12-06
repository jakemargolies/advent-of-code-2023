#include "day1.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <string>

int parse_digit(char character)
{
    int result = 0;

    if ((character >= 48) && (character <= 57))
    {
        result = character - 48;
    }

    return result;
}

int parse_digit(std::string str)
{
    std::array<std::string,9> digit_literals = 
        {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        
    int result = 0;

    for (int i = 0; i < digit_literals.size(); i++)
    {
        if (str.find(digit_literals[i]) != std::string::npos)
        {
            result = i + 1;
            break;
        }
    }
    return result;
}

int parse_first_number(std::string line)
{
    std::string sub_line;
    int result = 0;

    for (std::string::iterator it = line.begin(); it != line.end(); ++it)
    {
        if (int digit = parse_digit(*it))
        {
            result = digit;
            break;
        }

        sub_line += *it;
        if (int digit = parse_digit(sub_line))
        {
            result = digit;
            break;
        }
    }

    return result;
}

int parse_last_number(std::string line)
{
    std::string sub_line;
    int result = 0;

    for (std::string::reverse_iterator rit = line.rbegin(); rit != line.rend(); ++rit)
    {
        if (int digit = parse_digit(*rit))
        {
            result = digit;
            break;
        }

        sub_line = *rit + sub_line;
        if (int digit = parse_digit(sub_line))
        {
            result = digit;
            break;
        }
    }

    return result;
}
