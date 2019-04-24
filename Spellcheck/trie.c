#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

#define alphabet (26)

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

    claw = root;

    for(i=0; i<strlen(input_word); i++)
    {
        //convert letter to corresponsing trie node
        node_of_letter = (int)input_word[i] - 97;

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

trie* base_root;


bool load(const char *dictionary)
{
    base_root = init_node();

    add_entry(base_root, dictionary);

    return 0;
}


/*int main(void)
{
    char* word = "check";

    trie* root = init_node();

    add_entry(root, word);


}*/

