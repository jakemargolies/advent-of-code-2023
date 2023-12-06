#include <fstream>
#include <string>
#include <array>
#include <iostream>

#include "include/day1.hpp"

int main()
{
    std::string line;
    std::ifstream input_file("input.txt");

    int first_num;
    int last_num;
    int total_sum = 0;

    if (!input_file.is_open())
    {
        throw std::runtime_error("Input file is not open");
    }

    while (std::getline(input_file, line))
    {
        first_num = parse_first_number(line);
        last_num = parse_last_number(line);
        total_sum += (first_num * 10) + last_num;
        std::cout << "Line: " << first_num << last_num << "; Current Total: " << total_sum << std::endl;
    }

    std::cout << "Total Sum: " << total_sum << std::endl;
}