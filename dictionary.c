// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>
#include <strings.h>

#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
unsigned int tableCount = 0;
unsigned int wordCount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int h = hash(word);

    if (table[h] == NULL)
    {
        return false;
    }
    else if (strcasecmp(table[h]->word, word) == 0)
    {
        return true;
    }
    else
    {
        if (table[h]->next != NULL)
        {
            node *tmp = table[h]->next;
            while (tmp != NULL)
            {
                if (strcasecmp(tmp->word, word) == 0)
                {
                    return true;
                }
                tmp = tmp->next;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return toupper(word[0]) - 65;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    FILE *d = fopen(dictionary, "r");
    if (d == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    int index = 0;
    for (int c = fgetc(d); c != EOF; c = fgetc(d))
    {
        if (c != 10)
        {
            word[index] = c;
            index++;
        }
        else
        {
            //Create new node
            wordCount++;
            word[index] = '\0';
            node *n = malloc(sizeof(node));
            strcpy(n->word, word);
            //printf("%s\n", word);
            n->next = NULL;

            //hash and check for collisons
            int h = hash(word);

            if (table[h] == NULL)
            {
                table[h] = n;
            }
            else
            {
                n->next = table[h];
                table[h] = n;
            }
            tableCount++;

            index = 0;

        }




    }




    fclose(d);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            while (table[i]->next != NULL)
            {

                node *tmp = table[i];
                node *prev = NULL;

                while (tmp->next != NULL)
                {
                    prev = tmp;
                    tmp = tmp->next;
                    prev->next = NULL;
                }
                free(tmp);
                if (prev != NULL)
                {
                    prev->next = NULL;
                }

            }
            free(table[i]);
        }
    }
    return true;
}
