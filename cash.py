from cs50 import get_float

# Initialization
quarters = 0
dimes = 0
nickels = 0
pennies = 0

# Requesting a non-negative number, then formatting
m = get_float("Change owed: ")
while (m < 0):
    m = get_float("Change owed: ")
cents = round((m * 100))

# Count coins until none are left
while (cents > 0):

    # Quarter count
    while (cents >= 25):
        cents -= 25
        quarters += 1

    # Dime count
    while (cents >= 10 and cents < 25):
        cents -= 10
        dimes += 1

    # Nickel count
    while (cents >= 5 and cents < 10):
        cents -= 5
        nickels += 1

    # Penny count
    while (cents >= 1 and cents < 5):
        cents -= 1
        pennies += 1

# Printing coin counts

if (quarters == 1):
    print(f"{quarters} quarter owed")
else:
    print(f"{quarters} quarters owed")

if (dimes == 1):
    print(f"{dimes} dime owed")
else:
    print(f"{dimes} dimes owed")

if (nickels == 1):
    print(f"{nickels} nickel owed")
else:
    print(f"{nickels} nickels owed")

if (pennies == 1):
    print(f"{pennies} penny owed")
else:
    print(f"{pennies} pennies owed")

print("Optimized count count:")
print(f"{quarters + dimes + nickels + pennies}")