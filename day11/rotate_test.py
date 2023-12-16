# Assuming rotated_array is the result from the previous rotation
rotated_array = [
    [7, 4, 1],
    [8, 5, 2],
    [9, 6, 3]
]

# Rotate the array counterclockwise
original_array_back = [list(row) for row in reversed(list(zip(*rotated_array)))]

# Print the rotated and original arrays
print("Rotated Array:")
for row in rotated_array:
    print(row)

print("\nOriginal Array Back:")
for row in original_array_back:
    print(row)
