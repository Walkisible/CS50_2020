# Get the input
a = 0
while a < 1:
    n = input("Height: ")
    if n >= 1 and n <= 8:
        a += 1

#
a = 0
b = 0
c = 0
space = n - (a + 1)

for a in range(0, n):
    for b in range(0, space):
        print(" ", end="")

    space = space - 1

    for b in range(0, a + 1):
        print("#", end="")

    print("  ", end="")

    for c in range(0, a + 1):
        print("#", end="")

    print("\n", end="")
