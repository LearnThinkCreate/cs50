// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Word Count
int size_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int i = hash(word);

    for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// HASH FUNCTION FROM https://joseph28robinson.medium.com/cs50-pset-5-speller-f9c89d08237e
// Hashes word to a number
unsigned int hash(const char *word)
{
    // Function should take a string and return an index
    // This hash function adds the ASCII values of all characters in     the word together
    long sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // opening the file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open file - %s\n", dictionary);
        return false;
    }
    // Variables to read in the words
    char *word = malloc(LENGTH + 1);
    if (word == NULL)
    {
        free(word);
        return false;
    }
    // Reading in dictionary file char by char
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            free(word);
            free(n);
            printf("Malloc Failure");
            return false;
        }
        // Getting hash value
        int i = hash(word);

        // Adding the node to the begining of the linked list
        n->next = table[i];
        table[i] = n;

        // Copying word
        strcpy(n->word, word);

        // Saving time by keeping track of size in
        // the hash table itself
        size_count++;
    }
    // freeing malloc
    free(word);

    // closing file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return size_count;
}

// Frees linked list
void free_node(node *n)
{
    // TODO: Handle base case
    if (n == NULL)
    {
        return;
    }
    // TODO: Free parents
    else
    {
        free_node(n->next);
    }
    // TODO: Free child -- AKA: Free the current node
    free(n);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    for (int i = 0; i < N; i++)
    {
        free_node(table[i]);
    }
    return true;
}

