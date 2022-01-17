// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
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
const unsigned int N = (LENGTH+1) * 'z' ;

// Hash table
node *table[N];
int word_count = 0;


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int indx = hash(word);

    node *cursor = table[indx];
    while(cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    for (int i=0, n = strlen(word); i < n; i++)
    {
        sum += tolower(word[i]);
    }

    return (sum % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    //open the file in read mode
    FILE *p1 = fopen(dictionary, "r");

    if (p1 == NULL) return 0;

    // read one word at a time
    char tempWords[LENGTH+1];

    while(fscanf(p1, "%s", tempWords) != EOF)
    {

        node *n = malloc(sizeof(node));
        if (n == NULL) return false;

        strcpy(n->word,tempWords);
        n->next = NULL;
        // hash index
        int idx = hash(tempWords);

        if(table[idx]==NULL)
        {
            table[idx]=n;
        }
        else
        {
            n->next = table[idx];
            table[idx] = n;
        }
        word_count++;
    }
    fclose(p1);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //assign elements
    for(int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;

        while (cursor != NULL)

        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
