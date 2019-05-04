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

    if(!storage)
    {
        perror("error: not enough memory for malloc() in trim");
    }

    for(int i=0; i<=len; i++)
    {
        storage[i] = word[i];

    }

    return storage;
}

trie* base_root;

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

    trie*check = base_root;

    int node_of_letter;

    int j;

    for(j=0; j<strlen(lowercase_word); j++)
    {
        node_of_letter = (int)lowercase_word[j] - 97;

        if(lowercase_word[j]== '\'')
        {
            node_of_letter = 26;
        }

        if(check->nodes[node_of_letter])
        {
            check = check->nodes[node_of_letter];
        }

        else
        {
            free(lowercase_word);

            return false;
        }
    }

    free(lowercase_word);

    if(check->end_of_word == true)
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



    base_root = init_node();

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

            add_entry(base_root, new_word);

            free(new_word);

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

    char* last__word = trim(last_word, lw_index);

    add_entry(base_root, last__word);

    free(last__word);

    fclose(load_file);

    // trying to say if base_root is empty, but im not sure if this is the best way
    if(base_root != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
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
    freedom(base_root)
    return true;
}

/*
valgrind memcheck report

==1570== 
==1570== HEAP SUMMARY:
==1570==     in use at exit: 0 bytes in 0 blocks
==1570==   total heap usage: 527,931 allocs, 527,931 frees, 83,761,059 bytes allocated
==1570== 
==1570== All heap blocks were freed -- no leaks are possible
==1570== 
==1570== For counts of detected and suppressed errors, rerun with: -v
==1570== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
 */
