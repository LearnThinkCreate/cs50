#include <cs50.h>
#include <stdio.h>

int get_num_years(int start_size, int end_size);

int main(void)
{
    // Prompt for start size. Runs until startn > 0
    int start_n;
    do
    {
        start_n = get_int("Start size: ");
    }
    while (start_n < 9);

    // Promting user for end size. Runs until end_size >= start_size
    int end_n;
    do
    {
        end_n = get_int("End size: ");
    }
    while (end_n < start_n);

    int num_years = get_num_years(start_n, end_n);

    // Print number of years
    printf("Years: %i\n", num_years);
}


// Counts # years for llama pop to reach end size
int get_num_years(int start_size, int end_size)
{
    // Tracking the number of years and population
    int years = 0;
    int population = start_size;

    // Running until population reachs or surpasses the end size
    while (population < end_size)
    {
        population = population + (population / 3) - (population / 4);
        years++;
    }
    return years;
}