// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
// Creating Byte type for practice
typedef uint8_t BYTE;
// Uint16_t is not a hex, but it is of length 16
typedef int16_t HEX;

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

    //Copy header from input file to output file

    // Initialzing the buffer with malloc because I'm a fancy boy
    BYTE *header_buffer = malloc(HEADER_SIZE);

    // Reading in header to buffer
    fread(header_buffer, HEADER_SIZE, 1, input);
    // Copying the header to the output file
    fwrite(header_buffer, HEADER_SIZE, 1, output);

    // freeing memory like a good boy
    free(header_buffer);

    // Read samples from input file and write updated data to output file

    // Initializing sample buffer
    // I don't know the size so I'm not assigning one
    HEX sample_buffer;

    // Copying over the sample
    while (fread(&sample_buffer, sizeof(HEX), 1, input))
    {
        // Buffer is a varibale so it can be directly
        // multiplied by factor
        sample_buffer *= factor;

        fwrite(&sample_buffer, sizeof(HEX), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
