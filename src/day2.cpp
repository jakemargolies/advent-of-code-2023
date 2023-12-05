#include "day2.hpp"
#include "../previous_days/day1/include/day1.hpp"
#include <iostream>

bool is_possible_game(std::string game_line, int max_red, int max_blue, int max_green)
{
    std::string set;
    size_t set_end;
    while (!game_line.empty())
    {
        set_end = game_line.find("; ");
        set = game_line.substr(0, set_end);
        if (!is_possible_set(game_line.substr(0, set_end), max_red, max_blue, max_green))
        {
            return false;
        }
        game_line = game_line.substr(set_end + 2, std::string::npos);
    }
    return true;
}

bool is_possible_set(std::string set, int max_red, int max_blue, int max_green)
{
    bool result = false;

    int total_blue = 0;
    int total_red = 0;
    int total_green = 0;
    std::string digit_str;
    size_t end_of_entry;

    bool reached_end_of_set = false;
    while (!reached_end_of_set)
    {
        size_t trailing_ws_pos = set.find(" ");
        digit_str = set.substr(0, trailing_ws_pos);
        if (int digit = std::stoi(digit_str))
        {
            switch (set[trailing_ws_pos + 1])
            {
            case 'b':
                total_blue += digit;
                break;
            case 'r':
                total_red += digit;
                break;
            case 'g':
                total_green += digit;
                break;
            default:
                std::cout << "Uh... something is wrong." << std::endl;
            }
        }
        end_of_entry = set.find(", ");
        if (end_of_entry != std::string::npos)
        {
            set = set.substr(set.find(", ") + 2, std::string::npos);            
        }
        else
        {
            reached_end_of_set = true;
        }
    }

    if (!(total_blue > max_blue || total_red > max_red || total_green > max_green))
    {
        result = true;
    }

    return result;
}
