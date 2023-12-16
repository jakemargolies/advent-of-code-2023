def rotate_universe(universe, direction):
    match direction:
        case 'CW':
            return [list(row) for row in zip(*universe[::-1])]
        case 'CCW':
            return [list(row) for row in reversed(list(zip(*universe)))]


def expand_universe(universe_map, is_rotated):
    expanded_universe = []
    for row in universe_map:
        if '#' not in row:
            expanded_universe.append(['.'] * len(row))
        expanded_universe.append(row)
    if is_rotated:
        return rotate_universe(expanded_universe, 'CCW')
    else:   
        return expand_universe(rotate_universe(expanded_universe, 'CW'), True)

universe_map = []
galaxy_positions = []
with open('example-1.txt') as file:
    for line in file:
        universe_map.append(list(line.strip()))

universe_map = expand_universe(universe_map, False)
galaxy_id = 0
for i, row in enumerate(universe_map):
    for j, element in enumerate(row):
        if element == '#':
            galaxy_positions.append((i,j))
            universe_map[i][j] = galaxy_id
            galaxy_id += 1

print(galaxy_positions)
for row in universe_map:
    print(row)

while len(galaxy_positions) > 0:
    total_distance = 0
    start = galaxy_positions[0]
    galaxy_positions.pop(0)
    for end in galaxy_positions:
        distance = start[0]

