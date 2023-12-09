#include <list>
#include <string>

class KeyRangeEntry
{
private:
    long min;
    long max;
    long length;

public:
    KeyRangeEntry();
    KeyRangeEntry(long range_min, long range_length);
    long get_min() const;
    long get_max() const;
};

class MapRangeEntry
{
private:
    long src_max;

protected:
    long length;
    long src_min;
    long dst_min;

public:
    MapRangeEntry(std::string map_entry_line);

    MapRangeEntry();

    bool contains(long key) const;

    bool contains(KeyRangeEntry key_range_entry) const;

    long get_mapped_value(long key) const;

    KeyRangeEntry get_mapped_range(KeyRangeEntry key_range_entry, std::list<KeyRangeEntry>& leftover_key_ranges) const;
};


class Map : public std::list<MapRangeEntry>
{
public:
    long operator[](long key) const;

    std::list<KeyRangeEntry> operator[](KeyRangeEntry key_range_entry) const;
};

class SeedRangeList : public std::list<KeyRangeEntry>
{
public:
    SeedRangeList(std::string seeds_line);
};

void parse_seeds(std::list<long> *seeds, std::string seeds_line);

void parse_and_interpolate_seeds(std::list<long> *seeds, std::string seeds_line);