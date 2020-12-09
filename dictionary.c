// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"

// Including headers for string manipulation
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// Setting N to 26 squared
const unsigned int N = 676;

// Hash table
node *table[N];

// Initializing word count
int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO -- function COMPLETE

    // Indexing words with the hash function
    // Initializing traversal pointer
    int h_Index = 0;
    h_Index = hash(word);
    node *trav = table[h_Index];

    // Traverse table looking for word
    while (trav != NULL)
    {
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        }
        trav = trav->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO -- function COMPLETE

    int h_sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        h_sum = h_sum + tolower(word[i]);
    }
    int h_total = (h_sum % N);
    return h_total;

    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO -- function COMPLETE

    // Open dictionary file, check for errors
    FILE *file = fopen(dictionary, "r");
    char word[LENGTH + 1];
    if (file == NULL)
    {
        return false;
    }

    // Copy each word into word, hash each word
    while (fscanf(file, "%s", word) != EOF)
    {
        node *word_node = malloc(sizeof(node));
        if (word_node == NULL)
        {
            return false;
        }

        strcpy(word_node->word, word);
        word_node->next = NULL;

        // Indexing words, creating nodes for new words
        unsigned int w_Index = hash(word);
        if (table[w_Index] == NULL)
        {
            table[w_Index] = word_node;
        }

        // Inserting new nodes to beginning
        else
        {
            word_node->next = table[w_Index];
            table[w_Index] = word_node;
        }
        word_count++;
    }
    return true;
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO -- function COMPLETE
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO -- function COMPLETE

    // For each index in the hash table, free nodes
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *trav_free = head;
        while (cursor != NULL)
        {
            cursor = cursor -> next;
            free(trav_free);
            trav_free = cursor;
        }
        return true;
    }
    return false;
}
