with open('input-4.txt', 'r') as file:
    extrapolated_value_sum = 0
    for line in file:
        # Split the line into a list of strings
        values_str = line.split()

        # Convert each string to an integer
        values_int = [int(value) for value in values_str]

        # Generate list of diff sequences
        sequences = list([values_int])
        while any(num != 0 for num in sequences[-1]):
            diff_sequence = []
            number_to_subtract_from = values_int[0]

            for value in values_int[1:]:
                diff_sequence.append((value - number_to_subtract_from))
                number_to_subtract_from = value

            sequences.append(diff_sequence)
            values_int = diff_sequence

        # Extrapolate sequences
        sequences[-1].insert(0,0)
        index = len(sequences) - 2
        while index >= 0:
            sequences[index].insert(0, sequences[index][0] - sequences[index + 1][0])
            index -= 1

        extrapolated_value_sum += sequences[0][0]

print(extrapolated_value_sum)