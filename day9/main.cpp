#include <climits>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "include/day9.hpp"

#define INPUT_FILENAME "almanac.txt"

std::ifstream input_file(INPUT_FILENAME);
std::string line;
std::list<long> seeds;

Map seed_to_soil_map;
Map soil_to_fertilizer_map;
Map fertilizer_to_water_map;
Map water_to_light_map;
Map light_to_temp_map;
Map temp_to_hum_map;
Map hum_to_location_map;

std::list<Map> maps = {
    seed_to_soil_map,
    soil_to_fertilizer_map,
    fertilizer_to_water_map,
    water_to_light_map,
    light_to_temp_map,
    temp_to_hum_map,
    hum_to_location_map};

int part_1()
{
    // Extract seeds into list
    std::string seeds_line;
    std::getline(input_file, seeds_line);
    parse_seeds(&seeds, seeds_line);

    // Strip empty line
    std::getline(input_file, line);

    for (Map &map : maps)
    {
        // Strip header
        std::getline(input_file, line);

        // Populate map
        while (std::getline(input_file, line) && !line.empty())
        {
            MapRangeEntry entry(line);
            map.push_back(entry);
        }
    }

    long min_location = LONG_MAX;
    for (long seed : seeds)
    {
        long key = seed;
        for (Map &map : maps)
        {
            key = map[key];
        }
        long location = key;
        if (location < min_location)
        {
            min_location = location;
        }
    }

    std::cout << min_location << std::endl;

    return 0;
}

int part_2()
{
    // Extract seeds into list
    std::string seeds_line;
    std::getline(input_file, seeds_line);
    SeedRangeList seed_ranges(seeds_line);

    // Strip empty line
    std::getline(input_file, line);

    for (Map &map : maps)
    {
        // Strip header
        std::getline(input_file, line);

        // Populate map
        while (std::getline(input_file, line) && !line.empty())
        {
            MapRangeEntry entry(line);
            map.push_back(entry);
        }
    }

    long min_location = LONG_MAX;

    std::list<KeyRangeEntry> key_ranges = seed_ranges;
    for (Map &map : maps)
    {
        std::list<KeyRangeEntry> dst_ranges;
        std::list<KeyRangeEntry> new_key_ranges;
        while (!key_ranges.empty())
        {
            KeyRangeEntry key_range = key_ranges.back();
            key_ranges.pop_back();
            dst_ranges = map[key_range];
            for (KeyRangeEntry dst_range : dst_ranges)
            {
                new_key_ranges.push_back(dst_range);
            }
        }
        key_ranges = new_key_ranges;
    }
    for (KeyRangeEntry location_range : key_ranges)
    {
        if (location_range.get_min() < min_location)
        {
            min_location = location_range.get_min();
        }
    }

    return min_location;
}

int main()
{
    if (!input_file.is_open())
    {
        throw std::runtime_error("Input file is not open");
    }

    // std::cout << "Part 1 Answer: " << part_1() << std::endl;
    std::cout << "Part 2 Answer: " << part_2() << std::endl;
}
