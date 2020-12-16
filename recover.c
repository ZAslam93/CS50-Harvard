#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;
#define CHUNK_SIZE 512

int main(int argc, char *argv[])
{

    // Initialization
    int fcounter = 0;
    BYTE buffer[CHUNK_SIZE];
    int file1 = 0;
    char *filename;
    FILE *img = NULL;
    char eof;
    int read;

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
    while (1)
    {
        read = fread(buffer, sizeof(BYTE), CHUNK_SIZE, raw);
        if (read == 0)
        {
            break;
        }

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
                free(filename);
            }
            fcounter++;
        }
        // Continue writing if JPG signatures undetected
        else if (file1 == 1)
        {
            fwrite(buffer, sizeof(BYTE), read, img);
        }

    }
    fclose(raw);
    return 0;
}
