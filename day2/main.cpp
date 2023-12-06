#include "include/day2.hpp"
#include "../day1/include/day1.hpp"
#include <list>
#include <numeric>
#include <string>

#define MAX_RED 12
#define MAX_BLUE 14
#define MAX_GREEN 13

int main()
{
    int step_one_answer = 0;
    int step_two_answer = 0;
    std::string line;

    std::ifstream input_file("input.txt");
    if (!input_file.is_open())
    {
        throw std::runtime_error("Input file is not open");
    }

    while (std::getline(input_file, line))
    {
        int header_end = line.find(":");
        int game_id = std::stoi(line.substr(5, header_end - 5));
        std::string game_line = line.substr(header_end + 2, std::string::npos);
        if (is_possible_game(game_line, MAX_RED, MAX_BLUE, MAX_GREEN))
        {
            step_one_answer += game_id;
        }

        step_two_answer += calculate_cube_set_power(game_line);

    }

    std::cout << "Sum of possible game ids: " << step_one_answer << std::endl;
    std::cout << "Sum of powers: " << step_two_answer << std::endl;

    return 0;
}
