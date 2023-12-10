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

symbol_positions = []
for symbol_match in symbol_matches:
    symbol_positions.append(symbol_match.start())

print(symbol_positions)

valid_numbers = []

for number_match in number_matches:
    number = number_match.group()
    start = number_match.start()
    end = number_match.end() - 1
    number_length = end - start
    print(f"Number: {number}, Start: {start}, End: {end}")

    for sympos in symbol_positions:
        if ((sympos - 1) == end) | ((sympos + 1) == start):
            valid_numbers.append(int(number))
        elif ((sympos - line_length) <= end + 1) & ((sympos - line_length) >= start - 1):
            valid_numbers.append(int(number))
        elif ((sympos + line_length) <= end + 1) & ((sympos + line_length) >= start - 1):
            valid_numbers.append(int(number))


        
print(valid_numbers)
print(sum(valid_numbers))