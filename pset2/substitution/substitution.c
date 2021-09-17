#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool isvalkey(string key);

int main(int argc , string argv[])
{
    // Returning
    if (argc != 2)
    {
        printf("Pleae enter 1 argument\n");
        return 1;
    }
    else if (!isvalkey(argv[1])){
       printf("Please enter a valid key\n");
       return 1;
    }

    // Alphabet to index with key
    string alpha = "abcdefghijklmnopqrstuvwxyz{";
    // User input message
    string message = get_string("plaintext: ");

    // Encrypting the messge
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        char c = message[i];

        // looping through alphabet to find what letter c is
        for (int j = 0; alpha[j] <= tolower(c); j++)
        {
            if (alpha[j] == tolower(c))
            {
                /* if the message letter is upper case then making sure
                the replacement is also upper case */
                if (isupper(c))
                {
                    message[i] = toupper(argv[1][j]);
                }
                /* if the message letter is lowercase then making sure
                the replacement is also lower case */
                else
                {
                    message[i] = tolower(argv[1][j]);
                }
            }
        }

    }

    printf("ciphertext: %s" , message);
    printf("\n");

    return 0;

}

// Returns true is key is valid, false otherwise
bool isvalkey(string key)
{
    // array of characters- used to check each key item is a unique letter
    char abc[26];

    int nchar = strlen(key);

    // Returning false if the length of the key is not 26
    if(nchar != 26)
    {
        return false;
    }
    else
    {
        // Length is correct, now checking if the key is valid
        for (int i = 0; i < nchar; i++)
        {
            char c = key[i];

            // Checking if c is in the alphabet
            if (isalpha(c))
            {
                // All but the first characters are checed for uniqueness
                if (i >= 1)
                {
                    // Verifying the character is unique
                    for (int j = 0; j < i; j++)
                    {
                        // Returns false if the char is in the existing array
                        if (abc[j] == c)
                        {
                            return false;
                        }
                    }
                    // appending unique c to the array
                    abc[i] = c;
                }
                // The first character will automatically be appended
                else
                abc[i] = c;

            }
            // Returning false if c is not in the alphabet
            else
            {
                return false;
            }
        }
    }

    // If all conditions are met, return true
    return true;
}