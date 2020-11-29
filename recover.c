#include <stdio.h>
#include <stdlib.h>
// Include header files
#include <stdint.h>

typedef uint8_t BYTE;
#define CHUNK_SIZE 512

int main(int argc, char *argv[])
{
    //Defining BYTE, CHUNK_SIZE, initializing [fcounter] [file1] [filename] [*img]

    int fcounter = 0;
    BYTE buffer[CHUNK_SIZE];
    int file1 = 0;
    char *filename;
    FILE *img = NULL;
    char eof;

    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    // Opening file
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Reading file to buffer until EOF
    while (!feof(raw))
    {
        fread(buffer, sizeof(BYTE), CHUNK_SIZE, raw);

        // If JPG signatures identified
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Writing first JPG
            if (file1 == 0)
            {
                filename = malloc(sizeof(char) * 8);
                sprintf(filename, "%03i.jpg", fcounter);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), CHUNK_SIZE, img);
                file1 = 1;
                fcounter++;
                free(filename);
            }

            // Writing subsequent JPGs
            else
            {
                fclose(img);
                filename = malloc(sizeof(char) * 8);
                sprintf(filename, "%03i.jpg", fcounter);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), CHUNK_SIZE, img);
                fcounter++;
                free(filename);
            }
        }
        // Continue writing if JPG signatures undetected
        else if (file1 == 1)
        {
            fwrite(buffer, sizeof(BYTE), CHUNK_SIZE, img);
        }

    }
    fclose(raw);
    return 0;
}
