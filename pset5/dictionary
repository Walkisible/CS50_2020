// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100;

// Number of words
long word_count = 0;

bool loaded = false;

// Hash table
node *table[N];

// Node variables
node *n;
node *cursor;
node *tmp;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int h = hash(word);
    bool found = false;

    cursor = malloc(sizeof(node));
    if (cursor == NULL)
    {
        return false;
    }

    cursor->word[0] = '\0';
    cursor->next = table[h];

    while(cursor->next != NULL)
    {
        if (strcasecmp(word, cursor->word))
        {
            found = true;
            break;
        }
        else
        {
            cursor = cursor->next;
        }
    }


    free(cursor);
    return found;
}

// Hashes word to a number
// Hash function: first two letters
unsigned int hash(const char *word)
{
    int sum = 0;
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        sum += tolower(word[i]);
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char scan[LENGTH];

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    n = malloc(sizeof(node));
    if (n == NULL)
    {
        return false;
    }

    tmp = malloc(sizeof(node));
    if (tmp == NULL)
    {
        return false;
    }

    // Read strings from file "one at a time"
    while(fscanf(dict, "%s", scan) != EOF)
    {
        strcpy(n->word, scan);
        n->next = NULL;

        // Hash word to obtain a hash value
        int h = hash(n->word);

        // Insert node to hash table at that location
        if (table[h] == NULL)
        {
            table[h] = n;
        }
        else
        {
            tmp->next = n;

            n->next = table[h]->next;
            table[h]->next = n;

            tmp->next = NULL;
        }
        word_count++;
    }

    fclose(dict);
    free(tmp);

    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    long s = 0;

    if (loaded == true)
    {
        s = word_count;
    }
    else
    {
        s = 0;
    }
    return s;
}

// Unloads dictionary from memory, returning true if successful else false
// DEBUGGING THIS FUNCTION TO COMPLETE ALL
bool unload(void)
{
    long loop = 0;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        tmp = table[i];

        while(cursor != NULL)
        {
            cursor = cursor->next;
            tmp->next = NULL;
            tmp = cursor;
        }
    }
    free(n);
    free(tmp);
    free(cursor);

    return true;
}