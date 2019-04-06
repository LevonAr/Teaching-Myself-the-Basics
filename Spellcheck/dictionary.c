// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    // TODO
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *load_file = fopen(dictionary, "r");
    
    //lets figure out the fastes way to store each word in the least of memory
    
    // make it more accessible  ?maybe a trie? for check later on so our times are good
    
    //which of the following will be faster?
    
    //maybe if we do a for loop that looks for white space thus not using any extra memory, then we can test which one is the fastest down the line.
    
    
    fread
        
    scanf
        
    fgetc
        
    
    
    
    
    
    
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
