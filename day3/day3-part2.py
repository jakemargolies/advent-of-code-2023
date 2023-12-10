import re

schematic = [] 
with open('input.txt') as file:
    # for line in file:
    #     schematic.append(line.split())
    schematic = file.read()
    print(schematic)

line_length = schematic.find("\n") + 1

number_pattern = r'(?<![0-9])[0-9]+(?![0-9])|^[0-9]+'
symbol_pattern = r'([^0-9.\n])'

number_matches = re.finditer(number_pattern, schematic, flags=re.MULTILINE)
symbol_matches = re.finditer(symbol_pattern, schematic)

gear_positions = []
for symbol_match in symbol_matches:
    if symbol_match.group() == '*':
        gear_positions.append(symbol_match.start())

gears = {key: [] for key in gear_positions}
print(gear_positions)

for number_match in number_matches:
    number = number_match.group()
    start = number_match.start()
    end = number_match.end() - 1
    number_length = end - start
    print(f"Number: {number}, Start: {start}, End: {end}")

    for pos in gear_positions:
        if ((pos - 1) == end) | ((pos + 1) == start):
            gears[pos].append(int(number))
        elif ((pos - line_length) <= end + 1) & ((pos - line_length) >= start - 1):
            gears[pos].append(int(number))
        elif ((pos + line_length) <= end + 1) & ((pos + line_length) >= start - 1):
            gears[pos].append(int(number))

gear_ratios = []
for numbers in gears.values():
    if len(numbers) == 2:
        gear_ratios.append(numbers[0] * numbers[1])

print(gears) 
print(gear_ratios)      
print(sum(gear_ratios))