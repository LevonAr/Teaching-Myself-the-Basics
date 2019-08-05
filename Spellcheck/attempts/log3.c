// At this point I have got a trie and a hashtable to succesfully work with the following time stats ( THIS IS THE JANKY TRIE WITH TONS OF MEMORY LEAKS )

/*Janky Trie: 
TIME IN load:         0.35
TIME IN check:        0.02
TIME IN size:         0.00
TIME IN unload:       0.00
TIME IN TOTAL:        0.37
*/

/* Perfected trie 
WORDS MISSPELLED:     955
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        17756
TIME IN load:         0.28
TIME IN check:        0.02
TIME IN size:         0.00
TIME IN unload:       0.10
TIME IN TOTAL:        0.40
*/

/*
WORDS MISSPELLED:     955
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        17756
TIME IN load:         0.10
TIME IN check:        0.02
TIME IN size:         0.00
TIME IN unload:       0.02
TIME IN TOTAL:        0.13
*/


//I have two goals now. 
// Goal 1 - the more important goal: is to strenghten my understanding of how and why my programs work the way they do. 
// In other words I will make small tweaks and see if the program still works, and if it doesn't go into why.
// I especially feel like my hashtable program (although quicker) is very brittle, I will try to toughen it up. whatever that means

// Goal 2: make me programs work faster.

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

// technically alphabet and an apostrophe
#define alphabet (27)

typedef struct trie_
{
    struct trie_* nodes[alphabet];

    bool end_of_word;
} trie;

trie* init_node(void)
{
    trie* temp = malloc(sizeof(trie));

    if(!temp)
    {
        perror("error: not enough memory to initaize node");
    }

    temp->end_of_word = false;

    int i;

    for(i=0; i<alphabet; i++)
    {
        temp->nodes[i] = NULL;
    }

    return temp;
}


void add_entry(trie* claw, const char* input_word)
{
    // double for loop that increments chars in the word and increments through the trie pointers accordingly
    int i;

    //trie* claw = init_node();
    
    // run valgrind on control(trie.c) and experiment

    int node_of_letter;

    //claw = root;
    
    for(i=0; i<strlen(input_word); i++)
    {
        //convert letter to corresponsing trie node

