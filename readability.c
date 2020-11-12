#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)

{
    // Initializing variables [text] [Letters] [Sentences] [Words]
    string text = get_string("Text: ");
    int Letters = 0;
    int Sentences = 0;
    int Words = 1;

    // Iterating through each character in array [text]
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Counting uppercase and lowercase letters
        if ((int) text[i] >= 65 && (int) text[i] <= 90)
        Letters++;
        if ((int) text[i] >= 97 && (int) text[i] <= 122)
        Letters++;

        // Counting sentences
        if ((int) text[i] == 46 || (int) text[i] == 33 || (int) text[i] == 63)
        Sentences++;

        // Counting words
        if ((int) text[i] == 32)
        Words++;

    }

    // Computing values [L] and [S]
    float L = Letters * 100 / Words;
    float S = Sentences * 100 / Words;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Computing CL index, with conditions for extremeties
    printf("Coleman-Liau readability index:\n");
    if (index >= 16)
    printf("Grade 16+");
    else if (index <1)
    printf("Before Grade 1");
    else
    printf("Grade %i" , index);
}