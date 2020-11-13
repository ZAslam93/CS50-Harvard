#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    // Initializing variables [m] [quarters] [dimes] [nickels] [pennies]
    float m;
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;

    // Requesting a non-negative amount of change owed
    do
    {
        m = get_float("Change owed: ");
    }
    while (m < 0);

    // Rounding change owed to nearest cent, then formatting
    int cents = round(m * 100);

    // Iterating coin counting
    while (cents > 0)
    {

        // Quarter count
        while (cents >= 25)
        {
            cents = cents - 25;
            quarters++;
        }

        // Dime count
        while (cents >= 10 && cents < 25)
        {
            cents = cents - 10;
            dimes++;
        }

        // Nickel count
        while (cents >= 5 && cents < 10)
        {
            cents = cents - 5;
            nickels++;
        }

        // Penny count
        while (cents >= 1 && cents  < 5)
        {
            cents = cents - 1;
            pennies++;
        }
    }

    // Printing total count of coins
    if (quarters == 1)
    {
        printf("%i quarter owed\n", quarters);
    }
    else
    {
        printf("%i quarters owed\n", quarters);
    }

    if (dimes == 1)
    {
        printf("%i dime owed\n", dimes);
    }
    else
    {
        printf("%i dimes owed\n", dimes);
    }

    if (nickels == 1)
    {
        printf("%i nickel owed\n", nickels);
    }
    else
    {
        printf("%i nickels owed\n", nickels);
    }

    if (pennies == 1)
    {
        printf("%i penny owed\n", pennies);
    }
    else
    {
        printf("%i pennies owed\n", pennies);
    }

    printf("Optimized coin count:\n");

    printf("%i\n", quarters + dimes + nickels + pennies);
}
