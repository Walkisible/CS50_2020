import sys
import cs50
import csv

# Command line-arguments checking
if len(sys.argv) != 2:
    sys.exit(1)

# Open students.db
open(f"students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")
db.execute("CREATE TABLE students ( first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")

# Open characters.csv
table = []
with open(sys.argv[1], "r") as csv_file:
    data = csv.reader(csv_file, delimiter = ",")
    for row in data:
        table.append(row)
table.pop(0)

# Insert table[] into students.db
i = 0
for row in table:
    tmp = table[i][0].split()
    table[i].pop(0)
    j = 0
    for item in tmp:
        table[i].insert(j, tmp[j])
        j += 1
    i += 1

i = 0
for row in table:
    if len(row) != 5:
        table[i].insert(1, None)
    i += 1

i = 0
for row in table:
    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
               table[i][0], table[i][1], table[i][2], table[i][3], table[i][4])
    i += 1