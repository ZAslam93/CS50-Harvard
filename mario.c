#include <stdio.h>
#include <cs50.h>

int main(void)
{

    // Requesting value for variable [h] between 1 and 8 inclusive
    int h;
    do
    {
         h = get_int("Height:\n");
    }
          while (h<1 || h>8);

    // Constructing the pyramid
    for (int i = 0; i < h; i++)
    {
        //Creating horizontal spaces
        for (int s = h-1; s > i; s--)
        {
            printf(" ");
        }

        // Creating horizontal hashes
        for (int x = 0; x < i; x++)
        {
            printf("#");
        }

        // Generating a new line (vertical hashes)
        printf("#\n");
    }
}