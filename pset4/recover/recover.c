#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Please enter a file to be recovered.\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Initializing variables
    BYTE buffer[512];
    FILE *destination = NULL;
    int next_file = 0;
    char file_name[8];

    // Recover code
    while (fread(&buffer, 512, 1,  file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // closing the previous file
            if (next_file > 0)
            {
                fclose(destination);
            }

            sprintf(file_name, "%03i.jpg", next_file);

            // adding 1 to the next file
            next_file++;
            // Opening a new file for writing
            destination = fopen(file_name, "w");
            if (destination == NULL)
            {
                return 1;
            }
        }
        if (next_file > 0)
        {
            fwrite(&buffer, 512, 1, destination);
            if (destination == NULL)
            {
                return 1;
            }
        }
    }

    // Close file
    fclose(destination);
    fclose(file);
}