from sys import argv
import csv

# Open files
    # Open .csv file
database = []

with open(argv[1]) as csv_file:
    data = csv.reader(csv_file, delimiter=',')
    line_count = 0
    for row in data:
        i = 0
        database.append(row)
        line_count += 1
        i += 1

    # Open .text file
with open(argv[2]) as text_file:
    seq = text_file.read()

# Computing STR counts
STRs = database[0][1:len(seq) + 1]
STR_count = []
tmp_count = []
tmp = 0
count = 0
i = 0
for STR in STRs:
    j = 0
    for base in seq:
        k = j
        while seq[k:k + len(STRs[i])] == STRs[i]:
            count += 1
            k += len(STRs[i])

        if count > 0:
            tmp_count.append(count)
        else:
            tmp_count.append(0)

        count = 0
        k = 0
        j += 1

    tmp = max(tmp_count)
    STR_count.append(tmp)
    tmp_count.clear()
    i += 1

# Comparing against data
tmp_dataframe = []
dataframe = []
count_list = []
count = 0

i = 0
for element in database:
    tmp_dataframe.append(database[i][1:len(seq) + 1])
    i += 1
tmp_dataframe.pop(0)

n = 0
for sublist in tmp_dataframe:
    i = 0
    dataframe.append([])
    for number in tmp_dataframe[n]:
        x = int(tmp_dataframe[n][i])
        dataframe[n].append(x)
        i += 1
    n += 1

n = 0
for sublist in dataframe:
    i = 0
    for number in dataframe[n]:
        if STR_count[i] == dataframe[n][i]:
            count += 1
        i += 1
    count_list.append(count)
    count = 0
    n += 1

index = len(database[0]) - 1
checked = False
i = 0
c = 0
for sublist in count_list:
    if count_list[c] == index:
        checked = True
        break
    c += 1
    i += 1

database.pop(0)
if checked == True and c < line_count + 1:
    print(database[c][0])
else:
    print("No match")
