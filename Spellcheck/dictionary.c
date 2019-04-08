// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "dictionary.h"
#include <stdlib.h>


void store(char word[], int len);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    if (word)
    {
        true;
    }
    // TODO
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *load_file = fopen(dictionary, "r");

    //lets figure out the fastes way to store each word in the least of memory

    // make it more accessible  ?maybe a trie? for check later on so our times are good


    int index = 0;

    char dict_word[LENGTH + 1];

    for (int c = fgetc(load_file); c != EOF; c = fgetc(load_file))
    {

        if( c== '\n')
        {
            dict_word[index]= '\0';

            store(dict_word, index);

            index = 0;
        }

        else
        {
            dict_word[index]= c;

            index++;
        }



    }





    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}

void store(char word[], int len)
{
    char* storage = malloc(sizeof(char)*len);

    for(int i=0; i<=len; i++)
    {
        storage[i] = word[i];

    }

    printf("%s", storage);
}
