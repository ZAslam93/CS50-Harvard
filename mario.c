#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Requesting value for h between 1 and 8
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    // Constructing the pyramids
    for (int i = 0; i < h; i++)
    {
        // Left pyramid
        for (int s = h - 1; s > i; s--)
        {
            printf(" ");
        }
        for (int x = 0; x < i; x++)
        {
            printf("#");
        }
        printf("#");

        // Spaces
        printf("  ");

        // Right pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // Printing new row
        printf("#\n");
    }
}