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
    MapRangeEntry(std::string map_entry_line);

    bool contains(long key) const;

    long get_mapped_value(long key) const;
};

class Map : std::list<MapRangeEntry>
{
public:
    long &operator[](long key);
};

void parse_seeds(std::list<long> *seeds, std::string seeds_line);