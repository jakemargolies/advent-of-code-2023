import re
import math

tile_grid = []
pipe_chars = ['|', '-', 'L', 'J', '7', 'F']
grid_width = 0
grid_height = 0

def find_next_connected_pipe(current_pipe):
    pipe_shape = current_pipe[0]
    row, col = current_pipe[1]
    came_from = current_pipe[2]

    match pipe_shape:
        case '|':
            if came_from == 'north':
                return (tile_grid[row + 1][col], (row + 1, col), 'north')
            elif came_from == 'south':
                return (tile_grid[row - 1][col], (row - 1, col), 'south')
            else:
                raise ValueError('Invalid pipe direction')
        case '-':
            if came_from == 'west':
                return (tile_grid[row][col + 1], (row, col + 1), 'west')
            elif came_from == 'east':
                return (tile_grid[row][col - 1], (row, col - 1), 'east')
        case 'J':
            if came_from == 'north':
                return (tile_grid[row][col - 1], (row, col - 1), 'east')
            elif came_from == 'west':
                return (tile_grid[row - 1][col], (row - 1, col), 'south')
            else:
                raise ValueError('Invalid pipe direction')
        case 'L':
            if came_from == 'north':
                return (tile_grid[row][col + 1], (row, col + 1), 'west')
            elif came_from == 'east':
                return (tile_grid[row - 1][col], (row - 1, col), 'south')
            else:
                raise ValueError('Invalid pipe direction')
        case '7':
            if came_from == 'west':
                return (tile_grid[row + 1][col], (row + 1, col), 'north')
            elif came_from == 'south':
                return (tile_grid[row][col - 1], (row, col - 1), 'east')
            else:
                raise ValueError('Invalid pipe direction')
        case 'F':
            if came_from == 'east':
                return (tile_grid[row + 1][col], (row + 1, col), 'north')
            elif came_from == 'south':
                return (tile_grid[row][col + 1], (row, col + 1), 'west')
            else:
                raise ValueError('Invalid pipe direction')
        case 'S':
            # Check north
            if row > 0:
                if tile_grid[row - 1][col] in  ['|', '7', 'F']:
                    return (tile_grid[row - 1][col], (row - 1, col), 'south')
            # Check south
            if row < (len(tile_grid) - 1):
                if tile_grid[row + 1][col] in ['|', 'J', 'L']:
                    return (tile_grid[row + 1][col], (row + 1, col), 'north')
            # Check west
            if col > 0:
                if tile_grid[row][col - 1] in ['-', 'L', 'F']:
                    return (tile_grid[row][col - 1], (row, col - 1), 'east')
            # Check east
            if col < (len(tile_grid[0]) - 1):
                if tile_grid[row][col + 1] in ['-', 'J', '7']:
                    return (tile_grid[row][col + 1], (row, col + 1), 'west')


    # if (row > 0 & row < grid_height - 1) & (col > 0 & col < grid_width - 1):   
    #     # Check north
    #     if (tile_grid[row - 1][col] in ['|', '7', 'F', 'S']):
    #         return (tile_grid[row - 1][col], (row - 1, col), 'south')
    #     # Check south
    #     if (tile_grid[row + 1][col] in ['|', 'J', 'L', 'S']):
    #         return (tile_grid[row + 1][col], (row + 1, col), 'north')
    #     # Check east
    #     if (came_from != 'east') & (tile_grid[row][col + 1] in ['-', 'J', '7', 'S']):
    #         return (tile_grid[row][col + 1], (row, col + 1), 'west')
    #     # Check west
    #     if (came_from != 'west') & (tile_grid[row][col - 1] in ['-', 'F', 'L', 'S']):
    #         return (tile_grid[row][col - 1], (row, col - 1), 'east')
    # elif (row == 0 & (col > 0) & (col < grid_width -1)):
    #     # Check south
    #     if (came_from != 'south') & (tile_grid[row + 1][col] in ['|', 'J', 'L', 'S']):
    #         return (tile_grid[row + 1][col], (row + 1, col), 'north')
    #     # Check east
    #     if (came_from != 'east') & (tile_grid[row][col + 1] in ['-', 'J', '7', 'S']):
    #         return (tile_grid[row][col + 1], (row, col + 1), 'west')
    #     # Check west
    #     if (came_from != 'west') & (tile_grid[row][col - 1] in ['-', 'F', 'L', 'S']):
    #         return (tile_grid[row][col - 1], (row, col - 1), 'east')
        
        
# Find length of path
def find_loop_length(start_position):
    length = 0
    current_pipe = ('S', start_position, 'none')
    while True:
        current_pipe = find_next_connected_pipe(current_pipe)
        if(current_pipe[0] == 'S'):
            return length
        else:
            length += 1

def get_loop(start_position):
    current_pipe = ('S', start_position, 'none')
    loop = [current_pipe[1]]
    while True:
        current_pipe = find_next_connected_pipe(current_pipe)
        if (current_pipe[0] == 'S'):
            return loop
        loop.append(current_pipe[1])

with open('input.txt') as file:
    for line in file:
        tile_grid.append(list(line.strip()))
grid_height = len(tile_grid)
grid_width = len(tile_grid[0])

# Find all starting positions
start_positions = []
for i, tile_row in enumerate(tile_grid):
    for j, tile in enumerate(tile_row):
        if tile == 'S':
            start_positions.append((i, j))

for start_position in start_positions:
    print(f"Found starting position: [{start_position[0]}, {start_position[1]}]")
    print(f"Loop length: {find_loop_length(start_position)}")
    print(f"Longest path: {math.ceil(find_loop_length(start_position) / 2)}")

loop_tile_positions = get_loop(start_positions[0])
non_loop_tile_positions = []

for i, row in enumerate(tile_grid):
    for j, tile in enumerate(row):
        tile_position = (i, j)
        if tile_position not in loop_tile_positions:
            non_loop_tile_positions.append(tile_position)

num_enclosed_tiles = 0

for tile_position in non_loop_tile_positions:
    row = tile_position[0]
    col = tile_position[1]
    loop_crossings = 0
    riding_line_left = False
    riding_line_right = False
    while (row > 0) & (row < len(tile_grid) - 1) & (col > 0) & (col < len(tile_grid[0]) - 1):
        row += 1
        if ((row, col) in loop_tile_positions):
            match tile_grid[row][col]:
                case 'F':
                    riding_line_left = True
                case '7':
                    riding_line_right = True
                case 'J':
                    if riding_line_left:
                        loop_crossings += 1
                        riding_line_left = False
                    elif riding_line_right:
                        riding_line_right = False
                case 'L':
                    if riding_line_right:
                        loop_crossings += 1
                        riding_line_right = False
                    elif riding_line_left:
                        riding_line_left = False
                case '-':
                    loop_crossings += 1
                case 'S':
                    loop_crossings += 1

    if loop_crossings % 2 != 0:
        num_enclosed_tiles += 1

print('# of enclosed tiles: ' + str(num_enclosed_tiles))