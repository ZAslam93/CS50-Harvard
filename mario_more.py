from cs50 import get_int
h = 0

while h < 1 or h > 8:
    h = get_int("Height: ")


for i in range(h):

    # Left pyramid
    s = h - 1
    while (s > i):
        print(" ", end="")
        s -= 1
    x = 0
    while (x < i):
        print("#", end="")
        x += 1
    print("#", end="")

    # Spaces
    print("  ", end="")

    # Right pyramid
    j = 0
    while (j < i):
        print("#", end="")
        j += 1
    print("#")