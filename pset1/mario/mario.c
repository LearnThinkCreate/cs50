#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    // Loop that initiates each row
    for(int i = 0; i<height; i++)
    {
        // Leading # spaces before the #
        for(int s = height; s>i+1; s--)
        {
            printf(" ");
        }
        // Prints out the first set of #
        for(int j = 0; j<i+1; j++)
        {
            printf("#");
        }
        // Space between the two pyramids
        printf("  ");
        // Building the second pyramid
        for(int k = 0; k<i+1; k++)
        {
            printf("#");
        }
        // Adding new line for next set of rows
        printf("\n");
    }
}