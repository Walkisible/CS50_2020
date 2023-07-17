from cs50 import get_int

a = 0
while a < 1:
    n = get_int("Height: ")
    if n >= 1 and n <= 8:
        a += 1

i = 0
j = 0
space = n - (i + 1)

for i in range(0, n):
    for j in range(0, space):
        print(" ", end="")

    space = space - 1

    for j in range(0, i + 1):
        print("#", end="")

    print("\n", end="")
