#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

float *get_cli_coef(string text);

int main(void)
{
    string text = get_string("Text: ");

    // Coef is pointing to a float
    float *coef;

    coef = get_cli_coef(text);

    float L = coef[0];
    float S = coef[1];

    // Applying the cli formula... see get_cli_coef for details
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Printing the grade level of the text
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}

// The function returns a pointer to the cli_coef array
float * get_cli_coef(string text){
    // Setting the cli_coef to be a static (or global) variable/array
    static float cli_coef[2];

    // Variables that will be input to the cli_coef
    // Word starts with 1 since text end either with words or punctuation
    int word_count = 1;
    int letter_count = 0;
    int sentence_count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];

        if (isalpha(c)){
            letter_count++;
        }
        else if(isspace(c)){
            word_count++;
        }
        else if(c == '.' || c == '?' || c == '!')
        {
            sentence_count++;
        }
    }

    // Assigning values of S & L in Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
    cli_coef[0] = ((100.0 / word_count) * letter_count);
    cli_coef[1] = ((100.0 / word_count) * sentence_count);

    return cli_coef;
}