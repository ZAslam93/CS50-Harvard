// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef uint8_t BYTE;
typedef uint16_t SAMPLE;

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
// Buffer to store header and wav samples
BYTE header[44];
SAMPLE buffer;


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    fread(header, sizeof(BYTE), 44, input);
    fwrite(header, sizeof(BYTE), 44, output);
    
    // Read, write until EOF
    while (1)
    {
        int read = fread(&buffer, sizeof(SAMPLE), 1, input);
        if (read == 0)
        {
            break;
        }
        
        // Scaling buffer by factor provided
        SAMPLE scaled = buffer * factor;
        fwrite(&scaled, sizeof(SAMPLE), 1, output);
        
    }

    // Close files
    fclose(input);
    fclose(output);
}
