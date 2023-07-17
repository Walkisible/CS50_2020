from cs50 import get_float

a = 0

while a < 1:
    dollars = get_float("Change owed: ")

    if dollars > 0:
        a += 1

coins = round(dollars * 100)
count = 0

while coins >= 25:
    count += 1
    coins -= 25

while coins >= 10:
    count += 1
    coins -= 10

while coins >= 5:
    count += 1
    coins -= 5

while coins >= 1:
    count += 1
    coins -= 1

print(count)
