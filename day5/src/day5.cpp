#include <list>
#include <string>

#include "day5.hpp"

bool MapRangeEntry::contains(long key) const
{
    if (key < src_min || key > src_max)
    {
        return false;
    }
    return true;
}

bool MapRangeEntry::contains(KeyRangeEntry key_range_entry) const
{
    if (key_range_entry.get_min() > src_max || key_range_entry.get_max() < src_min)
    {
        return false;
    }
    return true;
}

long MapRangeEntry::get_mapped_value(long key) const
{
    long diff = key - this->src_min;
    return dst_min + diff;
}

KeyRangeEntry MapRangeEntry::get_mapped_range(KeyRangeEntry key_range_entry, std::list<KeyRangeEntry> &leftover_key_ranges) const
{
    long mapped_min;
    long mapped_length;
    long key_min = key_range_entry.get_min();
    long key_max = key_range_entry.get_max();

    if (src_min > key_min)
    {
        KeyRangeEntry new_leftover_range(key_min, src_min - key_min);
        leftover_key_ranges.push_back(new_leftover_range);
        if (key_max <= src_max)
        {
            mapped_length = key_max - src_min + 1;
        }
        else
        {
            mapped_length = src_max - src_min + 1;
            KeyRangeEntry new_leftover_range(src_max + 1, key_max - src_max);
            leftover_key_ranges.push_back(new_leftover_range);
        }
        mapped_min = dst_min;
    }
    else
    {
        if (key_max <= src_max)
        {
            mapped_length = key_max - key_min + 1;
        }
        else
        {
            mapped_length = src_max - key_min + 1;
            KeyRangeEntry new_leftover_range(src_max + 1, key_max - src_max);
            leftover_key_ranges.push_back(new_leftover_range);
        }
        mapped_min = this->get_mapped_value(key_min);
    }

    KeyRangeEntry mapped_range_entry(mapped_min, mapped_length);
    return mapped_range_entry;
}

MapRangeEntry::MapRangeEntry(){};

MapRangeEntry::MapRangeEntry(std::string map_entry_line)
{
    size_t end_of_dst = map_entry_line.find(" ");
    size_t end_of_src = map_entry_line.find(" ", end_of_dst + 1);

    std::string dst = map_entry_line.substr(0, end_of_dst);
    std::string src = map_entry_line.substr(end_of_dst + 1, end_of_src);
    std::string len = map_entry_line.substr(end_of_src + 1, std::string::npos);

    this->dst_min = std::stol(dst);
    this->src_min = std::stol(src);
    this->length = std::stol(len);

    this->src_max = src_min + length - 1;
}

KeyRangeEntry::KeyRangeEntry(){};

KeyRangeEntry::KeyRangeEntry(long range_min, long range_length)
{
    min = range_min;
    max = range_min + range_length - 1;
    length = range_length;
}

long KeyRangeEntry::get_min() const
{
    return min;
}

long KeyRangeEntry::get_max() const
{
    return max;
}

long Map::operator[](long key) const
{
    for (const MapRangeEntry range_entry : *this)
    {
        if (range_entry.contains(key))
        {
            long dst_value = range_entry.get_mapped_value(key);
            return dst_value;
        }
    }
    return key;
}

std::list<KeyRangeEntry> Map::operator[](KeyRangeEntry key_range) const
{
    std::list<KeyRangeEntry> dst_ranges;
    bool no_matches = true;
    std::list<KeyRangeEntry> leftover_key_ranges;
    for (const MapRangeEntry range_entry : *this)
    {
        for (auto it = leftover_key_ranges.begin(); it != leftover_key_ranges.end();)
        {
            if (range_entry.contains(*it))
            {
                dst_ranges.push_back(range_entry.get_mapped_range(*it, leftover_key_ranges));\
                it = leftover_key_ranges.erase(it);
            }
            else
            {
                it++;
            }
        }
        if (range_entry.contains(key_range))
        {
            dst_ranges.push_back(range_entry.get_mapped_range(key_range, leftover_key_ranges));
            no_matches = false;
        }
    }
    for (KeyRangeEntry leftover_key_range : leftover_key_ranges)
    {
        dst_ranges.push_back(leftover_key_range);
    }
    if (no_matches)
    {
        dst_ranges.push_back(key_range);
    }
    return dst_ranges;
}

SeedRangeList::SeedRangeList(std::string seeds_line)
{
    size_t end_of_range_start;
    size_t end_of_range_length;
    std::string range_start;
    std::string range_length;
    size_t next_seed_position = seeds_line.find(" ");
    while (next_seed_position != std::string::npos)
    {
        next_seed_position += 1;
        seeds_line = seeds_line.substr(next_seed_position, std::string::npos);
        end_of_range_start = seeds_line.find(" ");
        range_start = seeds_line.substr(0, end_of_range_start);
        seeds_line = seeds_line.substr(end_of_range_start + 1, std::string::npos);
        end_of_range_length = seeds_line.find(" ");
        range_length = seeds_line.substr(0, end_of_range_length);

        KeyRangeEntry new_range_entry(std::stol(range_start), std::stol(range_length));
        this->push_back(new_range_entry);
        next_seed_position = seeds_line.find(" ");
    }
}

void parse_seeds(std::list<long> *seeds, std::string seeds_line)
{
    size_t end_of_seed;
    long new_seed;
    size_t next_seed_position = seeds_line.find(" ");
    while (next_seed_position != std::string::npos)
    {
        next_seed_position += 1;
        seeds_line = seeds_line.substr(next_seed_position, std::string::npos);
        end_of_seed = seeds_line.find(" ");
        new_seed = std::stol(seeds_line.substr(0, end_of_seed));
        seeds->push_back(new_seed);
        next_seed_position = seeds_line.find(" ");
    }
    return;
}

void parse_and_interpolate_seeds(std::list<long> *seeds, std::string seeds_line)
{
    size_t end_of_seed_start;
    size_t end_of_seed_range;
    long seed_start;
    long seed_range;
    size_t next_seed_position = seeds_line.find(" ");
    while (next_seed_position != std::string::npos)
    {
        next_seed_position += 1;
        seeds_line = seeds_line.substr(next_seed_position, std::string::npos);
        end_of_seed_start = seeds_line.find(" ");
        seed_start = std::stol(seeds_line.substr(0, end_of_seed_start));
        seeds_line = seeds_line.substr(end_of_seed_start + 1, std::string::npos);
        end_of_seed_range = seeds_line.find(" ");

        seeds->push_back(seed_start);
    }
}
