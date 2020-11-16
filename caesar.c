#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // Checking for any non-decimals in argument
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (argv[1][i] < 47 || argv[1][i] > 58)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        // Main program -- Key validated

        // Requesting string [plain] to be encrypted, initializing key [k]
        string plain = get_string("plaintext: ");
        int k = atoi(argv[1]);

        // Reducing [k] to usable value
        if (k >= 26)
        {
            k = k % 26;
        }
        
        // Encrypting alphabetical characters only
        for (int j = 0, p = strlen(plain); j < p; j++)
        {
            // Encrypting uppercase characters
            if (isupper(plain[j]))
            {
                plain[j] = ((plain[j] - 65 + k) % 26) + 65;
            }

            // Encrypting lowercase characters
            else if (islower(plain[j]))
            {
                plain[j] = ((plain[j] - 97 + k) % 26) + 97;

            }
        }
        printf("ciphertext: %s\n", plain);
        return 0;
    }
    // Error -- no inputs or more than 1 argument on command line
    else
    {
        printf("Usage: ./caesar key\n");
    }
    return 1;
}