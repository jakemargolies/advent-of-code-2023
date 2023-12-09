# Open the file in read mode
with open('input-3.txt', 'r') as file:
    # Read the seed ranges
    seeds_line_as_list = file.readline().strip('seeds: \n').split(' ')
    seed_ranges = {seeds_line_as_list[0::2], seeds_line_as_list[1::2]}
    print(seed_ranges)

    for min_val in seed_ranges:
        length = seed_ranges[min_val]
        