from cs50 import get_int

# Requesting a height between 1 and 8
h = get_int("Height: ")
while (h < 1 or h > 8):
    h = get_int("Height: ")


# Constructing the pyramid
for i in range(h):

    # Horizontal spaces
    s = h - 1
    while (s > i):
        s -= 1
        print(" ", end = "")

    # Horizontal hashes
    x = 0
    while (x < i):
        print("#", end = "")
        x += 1

    # Generating a new line (vertical hashes)
    print("#")