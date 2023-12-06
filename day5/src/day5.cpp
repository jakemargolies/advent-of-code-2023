#include <list>
#include <string>

class MapRangeEntry
{
private:
    long length;
    long src_start;
    long src_end;
    long dst_start;

public:
    MapRangeEntry(std::string map_entry_line)
    {
        size_t end_of_dst = map_entry_line.find(" ");
        size_t end_of_src = map_entry_line.find(" ", end_of_dst);

        std::string dst = map_entry_line.substr(0, end_of_dst);
        std::string src = map_entry_line.substr(end_of_dst + 1, end_of_src);
        std::string len = map_entry_line.substr(end_of_src + 1, std::string::npos);

        this->dst_start = std::stol(dst);
        this->src_start = std::stol(src);
        this->length = std::stol(len);

        this->src_end = src_start + length;
    }

    bool contains(long key) const
    {
        if (key < src_start || key > src_end)
        {
            return false;
        }
        return true;
    }

    long get_mapped_value(long key) const
    {
        long diff = key - src_start;
        return dst_start + diff;
    }
};

class Map : std::list<MapRangeEntry>
{
public:
    long &operator[](long key)
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
};

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
