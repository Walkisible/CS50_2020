import sys
import cs50

# Command line-arguments checking
if len(sys.argv) != 2:
    sys.exit(1)

# Get argv
house = sys.argv[1]

# Open students.db
open(f"students.db", "r").close()
db = cs50.SQL("sqlite:///students.db")
result = db.execute("SELECT students.first, students.middle, students.last, students.birth FROM students WHERE students.house == ? GROUP BY students.first ORDER BY students.last", house)

tmp = []
for row in result:
    for key, val in row.items():
        tmp.append(val)

i = 0
for item in tmp:
    if i % 4 == 0:
        print(tmp[i], end="")
    if i % 4 == 1:
        if tmp[i] != None:
            print(" %s" % tmp[i], end="")
    if i % 4 == 2:
        print(" %s" % tmp[i], end="")
    if i % 4 == 3:
        print(", born %d" % tmp[i])
    i += 1