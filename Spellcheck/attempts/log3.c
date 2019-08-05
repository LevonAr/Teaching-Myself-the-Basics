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

        node_of_letter = (int)input_word[i] - 97;

        if(input_word[i]== '\'')
        {
            node_of_letter = 26;
        }


        if (claw->nodes[node_of_letter])
        {
            claw = claw->nodes[node_of_letter];
        }

        else
        {
            claw->nodes[node_of_letter] = init_node();

            claw = claw->nodes[node_of_letter];
        }
    }

    claw->end_of_word = true;
}

char* trim(char word[], int len)
{
    char* storage = malloc(sizeof(char)*(len+1));

    for(int i=0; i<=len; i++)
    {
        storage[i] = word[i];

    }

    return storage;
}

trie base_root;

int dict_size;

bool check(const char *word)
{
    char* lowercase_word = malloc((strlen(word)+1)*sizeof(char)) ;

    int i;

    for(i=0; i<strlen(word); i++)
    {
        lowercase_word[i] = tolower(word[i]);
    }

    lowercase_word[i]= '\0';

    trie* check_claw = init_node();

    check_claw = &base_root;

    int node_of_letter;

    int j;

    for(j=0; j<strlen(lowercase_word); j++)
    {
        node_of_letter = (int)lowercase_word[j] - 97;

        if(lowercase_word[j]== '\'')
        {
            node_of_letter = 26;
        }

        if(check_claw->nodes[node_of_letter])
        {
            check_claw = check_claw->nodes[node_of_letter];
        }

        else
        {
            return false;
        }
    }

    if(check_claw->end_of_word == true)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool load(const char *dictionary)
{
    FILE *load_file = fopen(dictionary, "r");

    if(!load_file)
    {
        printf("%s", "could not open dictionary");

        return false;
    }

    trie* base_root_Ptr = &base_root;

    base_root_Ptr = init_node();

    int new_line_counter = 1;

    for (int c = fgetc(load_file); c != EOF; c = fgetc(load_file))
    {
        if( c== '\n')
        {
            new_line_counter++;
        }

    }

    dict_size = new_line_counter;

    fseek(load_file, 0, SEEK_SET);

    int index = 0;

    char dict_word[LENGTH + 1];

    int last_word_counter = 0;

    //last word index
    int lw_index = 0;

    char last_word[LENGTH + 1];

    for (int c = fgetc(load_file); c != EOF; c = fgetc(load_file))
    {

        if( c== '\n')
        {
            dict_word[index]= '\0';

            char* new_word = trim(dict_word, index);

            add_entry(&base_root, new_word);

            index = 0;

            last_word_counter ++;
        }

        else if(last_word_counter == dict_size -1)
        {
            last_word[lw_index] = c;

            lw_index++;
        }

        else
        {
            dict_word[index]= c;

            index++;
        }

    }
    last_word[lw_index] = '\0';

    char* last__word = trim(last_word, lw_index-1);

    add_entry(&base_root, last__word);

    int k;

    for(k=0; k<alphabet; k++)
    {
        if(base_root.nodes[k]!=NULL)
        return true;
    }

    return false;
}

unsigned int size(void)
{
    if(!dict_size)
    {
        perror("error: dictionary size does not exist");

        return -1;
    }

    return dict_size;
}

void freedom(trie* node_to_free)
{
    for(int i=0; i<alphabet; i++)
    {
        if(node_to_free->nodes[i])
        {
            freedom(node_to_free->nodes[i]);
        }
    }

    free(node_to_free);
}
bool unload(void)
{
    freedom(base_root);

    return true;
}

/*
Janky trie memcheck report 


==14624== 
==14624== HEAP SUMMARY:
==14624==     in use at exit: 119,789,994 bytes in 688,776 blocks
==14624==   total heap usage: 688,778 allocs, 2 frees, 119,790,786 bytes allocated
==14624== 
==14624== 7 bytes in 1 blocks are definitely lost in loss record 1 of 13
==14624==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14624==    by 0x422C4A: trim (dictionary.c:84)
==14624==    by 0x423B8B: load (dictionary.c:233)
==14624==    by 0x420942: main (speller.c:40)
==14624== 
==14624== 224 bytes in 1 blocks are definitely lost in loss record 2 of 13
==14624==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14624==    by 0x4222E3: init_node (dictionary.c:22)
==14624==    by 0x422527: add_entry (dictionary.c:47)
==14624==    by 0x423BA6: load (dictionary.c:235)
==14624==    by 0x420942: main (speller.c:40)
==14624== 
==14624== 672 bytes in 3 blocks are possibly lost in loss record 4 of 13
==14624==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14624==    by 0x4222E3: init_node (dictionary.c:22)
==14624==    by 0x422527: add_entry (dictionary.c:47)
==14624==    by 0x423790: load (dictionary.c:208)
==14624==    by 0x420942: main (speller.c:40)
==14624== 
==14624== 9,184 bytes in 41 blocks are possibly lost in loss record 7 of 13
==14624==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14624==    by 0x4222E3: init_node (dictionary.c:22)
==14624==    by 0x422891: add_entry (dictionary.c:73)
==14624==    by 0x423790: load (dictionary.c:208)
==14624==    by 0x420942: main (speller.c:40)
==14624== 
==14624== 94,327 bytes in 17,756 blocks are definitely lost in loss record 8 of 13
==14624==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14624==    by 0x422DEB: check (dictionary.c:108)
==14624==    by 0x421313: main (speller.c:112)
==14624== 
==14624== 1,439,220 bytes in 143,090 blocks are definitely lost in loss record 9 of 13
==14624==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14624==    by 0x422C4A: trim (dictionary.c:84)
==14624==    by 0x423775: load (dictionary.c:206)
==14624==    by 0x420942: main (speller.c:40)
==14624== 
==14624== 3,977,344 bytes in 17,756 blocks are definitely lost in loss record 10 of 13
==14624==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14624==    by 0x4222E3: init_node (dictionary.c:22)
==14624==    by 0x422FA7: check (dictionary.c:119)
==14624==    by 0x421313: main (speller.c:112)
==14624== 
==14624== 32,051,488 bytes in 143,087 blocks are definitely lost in loss record 11 of 13
==14624==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14624==    by 0x4222E3: init_node (dictionary.c:22)
==14624==    by 0x422527: add_entry (dictionary.c:47)
==14624==    by 0x423790: load (dictionary.c:208)
==14624==    by 0x420942: main (speller.c:40)
==14624== 
==14624== 82,215,392 (5,824 direct, 82,209,568 indirect) bytes in 26 blocks are definitely lost in loss record 13 of 13
==14624==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14624==    by 0x4222E3: init_node (dictionary.c:22)
==14624==    by 0x422891: add_entry (dictionary.c:73)
==14624==    by 0x423790: load (dictionary.c:208)
==14624==    by 0x420942: main (speller.c:40)
==14624== 
==14624== LEAK SUMMARY:
==14624==    definitely lost: 37,568,434 bytes in 321,717 blocks
==14624==    indirectly lost: 82,209,568 bytes in 367,007 blocks
==14624==      possibly lost: 9,856 bytes in 44 blocks
==14624==    still reachable: 2,136 bytes in 8 blocks
==14624==         suppressed: 0 bytes in 0 blocks
==14624== Reachable blocks (those to which a pointer was found) are not shown.
==14624== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==14624== 
==14624== For counts of detected and suppressed errors, rerun with: -v
==14624== ERROR SUMMARY: 17 errors from 10 contexts (suppressed: 0 from 0)
*/
