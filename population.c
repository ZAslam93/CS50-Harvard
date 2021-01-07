#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Requesting starting size of population
    int s;
    do
    {
        s = get_int("Start size: ");
    }
    while (s < 9);
    
    // Requesting end size of population
    int e;
    do
    {
        e = get_int("End size: ");
    }
    while (e < s);
    
    // Update population every year until end size is met
    int n = 0; 
    while (s < e)
    {
        n++;
        s = s + (s / 3) - (s / 4);
       
    }
    
    // Print number of years needed to reach end size
    printf("Years: %i", n);
}