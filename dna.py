import sys
import csv
import re

# Opening files and storing into variables, initializing
database = open(sys.argv[1])
sequence = open(sys.argv[2])
db = csv.reader(database)
key_string = next(db)
seq_string = sequence.read()
STR_count = [-1] * len(key_string)

# For each sequence in key_string, search across seq_string
for k in range(1, len(key_string)):
    for i in range(len(seq_string)):
        count = 0
        # If the STR is found, search for consecutive STRs
        if key_string[k] == seq_string[i: i + len(key_string[k])]:
            count += 1
            start_ind = i + len(key_string[k])
            end_ind = start_ind + len(key_string[k])
            while key_string[k] == seq_string[start_ind:end_ind]:
                count += 1
                start_ind = i + len(key_string[k]) * count
                end_ind = start_ind + len(key_string[k])
        # If a new highest count is found, update
        if count > STR_count[k]:
            STR_count[k] = count

# After STR_count is populated, close files
database.close()
sequence.close()

# Opening csv to compare against STR_count
db_2 = open(sys.argv[1])
reader = csv.reader(db_2)

# Eliminating header data for comparison
header = next(reader)

# For each row, compare row's STR against STR_count
for row in reader:
    matches = 0
    for j in range(1, len(key_string)):
        if STR_count[j] == int(row[j]):
            matches += 1
            # If all STRs match, output name, close and conclude
            if matches == len(key_string) - 1:
                print(row[0])
                db_2.close()
                exit()

# No complete match exists. Close and conclude
print("No match")
db_2.close()
exit()