#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    // Initialization
    int index = 0;
    int checksum = 0;
    long cc = get_long("Enter a valid credit card number: \n");
    long cc_copy = cc;
    long n = 0;
    int flag = -1;

    // Luhn's algorithm
    while (cc > 1)
    {
        n = cc % 10;
        index++;
        if ((index % 2) == 0)
        {
            n = (n * 2);
            while (n >= 10)
            {
                long n1 = (n % 10);
                n = n / 10;
                long n2 = (n % 10);
                n = (n1 + n2);
            }
        }
        checksum += n;
        cc = (cc / 10);
    }

    // If cc passed checksum, analyze what type of card it represents
    if ((checksum % 10) == 0)
    {
        // American Express check
        long cc_amex = (cc_copy / (long) pow(10, 13));
        if (((cc_amex / 10) % 10 == 3) && ((cc_amex % 10 == 7) || (cc_amex % 10 == 4)))
        {
            printf("AMEX\n");
            return 0;
        }

        // Mastercard check
        long cc_master = (cc_copy / (long) pow(10, 14));
        if ((cc_master > 50 && cc_master < 56))
        {
            printf("MASTERCARD\n");
            return 0;
        }

        // Visa check
        long cc_visa = (cc_copy / (long) pow(10, 12));
        long cc_visa2 = (cc_copy / (long) pow(10, 15));
        if (cc_visa == 4 || cc_visa2 == 4)
        {
            printf("VISA\n");
            return 0;
        }

        // If cc fails all checks, it is invalid
        printf("INVALID\n");
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}