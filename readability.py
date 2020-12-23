from cs50 import get_string

# Requesting text to be analyzed, initializing counters
l = 0
s = 0
w = 1
text = get_string("Text: ")

# Iterating through each character

for i in range(len(text)):

    # Counting uppercase letters
    if (ord(text[i]) >= 65 and ord(text[i]) <= 90):
        l += 1

    # Counting lowercase letters
    if (ord(text[i]) >= 97 and ord(text[i]) <= 122):
        l += 1

    # Counting sentences
    if (ord(text[i]) == 46 or ord(text[i]) == 33 or ord(text[i]) == 63):
        s += 1

    # Counting words
    if (ord(text[i]) == 32):
        w += 1

# Computing values L and S for CL index
L = (float(l) * 100 / w)
S = (float(s) * 100 / w)
index = round(0.0588 * L - 0.296 * S - 15.8)

# Expressing CL index
if (index >= 16):
    print("Grade 16+")
elif (index < 1):
    print("Before Grade 1")
else:
    print(f"Grade {index}")