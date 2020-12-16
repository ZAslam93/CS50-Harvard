from cs50 import get_int
import sys

# Initialization
index = 0
checksum = 0
cc = get_int("Enter a valid credit card number: ")
cc_copy = cc
n = 0

# Luhn's algorithm
while (cc > 1):
    n = cc % 10
    index += 1

    # If number is indexed even, treat separately
    if ((index % 2) == 0):
        n = n * 2
        while (n >= 10):
            n1 = (n % 10)
            n = n // 10
            n2 = (n % 10)
            n = n1 + n2
    checksum += n
    cc = cc // 10

# If cc passed checksum, analyze to discover card type
if ((checksum % 10) == 0):

    # American Express check
    cc_amex = (cc_copy // pow(10, 13))
    if ((cc_amex % 10 == 4) or (cc_amex % 10 == 7)):
        if ((cc_amex // 10) % 10 == 3):
            print("AMEX")
            sys.exit(0)

    # Mastercard check
    cc_master = (cc_copy // pow(10, 14))
    if ((cc_master > 50 and cc_master < 56)):
        print("MASTERCARD")
        sys.exit(0)

    # Visa check
    cc_visa = (cc_copy // pow(10, 12))
    cc_visa2 = (cc_copy // pow(10, 15))
    if (cc_visa == 4 or cc_visa2 == 4):
        print("VISA")
        sys.exit(0)
else:
    print("INVALID")
    sys.exit(0)