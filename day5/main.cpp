#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "include/day5.hpp"

#define INPUT_FILENAME "almanac.txt"

int main()
{

    std::string line;
    std::list<long> seeds;
    Map seed_to_soil_map;
    Map soil_to_fertilizer_map;
    Map fertilizer_to_water_map;
    Map water_to_light_map;
    Map light_to_temp_map;
    Map temp_to_hum_map;
    Map hum_to_location_map;

    std::ifstream input_file(INPUT_FILENAME);
    if (!input_file.is_open())
    {
        throw std::runtime_error("Input file is not open");
    }

    std::string seeds_line;
    std::getline(input_file, seeds_line);
    parse_seeds(&seeds, seeds_line);

    for (long seed : seeds)
    {
        std::cout << seed << std::endl;
    }
}
