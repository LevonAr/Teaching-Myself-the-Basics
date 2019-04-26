// At this point I have got a trie and a hashtable to succesfully work with the following time stats

/*Trie: 
TIME IN load:         0.35
TIME IN check:        0.02
TIME IN size:         0.00
TIME IN unload:       0.00
TIME IN TOTAL:        0.37
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


void add_entry(trie* root, const char* input_word)
{
    // double for loop that increments chars in the word and increments through the trie pointers accordingly
    int i;

    trie* claw = init_node();

    int node_of_letter;

    claw = root;// okay, why does this work, lets see what happens when i alter it

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

bool unload(void)
{
    /*free(base_root);

    base_root = NULL;

    if(base_root)
    {
        return false;
    }*/

    return true;
}
