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

    int node_of_letter;

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

    if(check->end_of_word == true)
    {
        return true;
    }

    else
    {
        return false;
    }
    
    free(lowercase_word);

}

bool load(const char *dictionary)
{
    FILE *load_file = fopen(dictionary, "r");

    if(!load_file)
    {
        printf("%s", "could not open dictionary");

        return false;
    }


    
    //XXXX HERE  XXXXX
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

    char* last__word = trim(last_word, lw_index-1);

    add_entry(base_root, last__word);
    
    free(last__word);

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
    freedom(base_root);

    return true;
}

    
    //XXXXX  HERE  XXXXXX
    
    /*free(base_root);

    base_root = NULL;

    if(base_root)
    {
        return false;
    }*/

// Valgrind output with leak report
/*
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


/*

after removing free(base_root) from unload

HEAP SUMMARY:
==14760==     in use at exit: 119,790,218 bytes in 688,777 blocks
==14760==   total heap usage: 688,778 allocs, 1 frees, 119,790,786 bytes allocated
==14760== 
==14760== 7 bytes in 1 blocks are definitely lost in loss record 1 of 11
==14760==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14760==    by 0x422BFA: trim (dictionary.c:84)
==14760==    by 0x423B3B: load (dictionary.c:233)
==14760==    by 0x4208F2: main (speller.c:40)
==14760== 
==14760== 224 bytes in 1 blocks are definitely lost in loss record 3 of 11
==14760==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14760==    by 0x422293: init_node (dictionary.c:22)
==14760==    by 0x4224D7: add_entry (dictionary.c:47)
==14760==    by 0x423B56: load (dictionary.c:235)
==14760==    by 0x4208F2: main (speller.c:40)
==14760== 
==14760== 672 bytes in 3 blocks are possibly lost in loss record 5 of 11
==14760==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14760==    by 0x422293: init_node (dictionary.c:22)
==14760==    by 0x4224D7: add_entry (dictionary.c:47)
==14760==    by 0x423740: load (dictionary.c:208)
==14760==    by 0x4208F2: main (speller.c:40)
==14760== 
==14760== 94,327 bytes in 17,756 blocks are definitely lost in loss record 7 of 11
==14760==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14760==    by 0x422D9B: check (dictionary.c:108)
==14760==    by 0x4212C3: main (speller.c:112)
==14760== 
==14760== 1,439,220 bytes in 143,090 blocks are definitely lost in loss record 8 of 11
==14760==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14760==    by 0x422BFA: trim (dictionary.c:84)
==14760==    by 0x423725: load (dictionary.c:206)
==14760==    by 0x4208F2: main (speller.c:40)
==14760== 
==14760== 3,977,344 bytes in 17,756 blocks are definitely lost in loss record 9 of 11
==14760==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14760==    by 0x422293: init_node (dictionary.c:22)
==14760==    by 0x422F57: check (dictionary.c:119)
==14760==    by 0x4212C3: main (speller.c:112)
==14760== 
==14760== 32,051,488 bytes in 143,087 blocks are definitely lost in loss record 10 of 11
==14760==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14760==    by 0x422293: init_node (dictionary.c:22)
==14760==    by 0x4224D7: add_entry (dictionary.c:47)
==14760==    by 0x423740: load (dictionary.c:208)
==14760==    by 0x4208F2: main (speller.c:40)
==14760== 
==14760== LEAK SUMMARY:
==14760==    definitely lost: 37,562,610 bytes in 321,691 blocks
==14760==    indirectly lost: 0 bytes in 0 blocks
==14760==      possibly lost: 672 bytes in 3 blocks
==14760==    still reachable: 82,226,936 bytes in 367,083 blocks
==14760==         suppressed: 0 bytes in 0 blocks
==14760== Reachable blocks (those to which a pointer was found) are not shown.
==14760== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==14760== 
==14760== For counts of detected and suppressed errors, rerun with: -v
==14760== ERROR SUMMARY: 15 errors from 8 contexts (suppressed: 0 from 0)
    */

/*

report after new code for unload

=11141== 
==11141== HEAP SUMMARY:
==11141==     in use at exit: 5,511,466 bytes in 178,604 blocks
==11141==   total heap usage: 545,687 allocs, 367,083 frees, 87,738,402 bytes allocated
==11141== 
==11141== 7 bytes in 1 blocks are definitely lost in loss record 1 of 6
==11141==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==11141==    by 0x422C2A: trim (dictionary.c:84)
==11141==    by 0x423B6B: load (dictionary.c:233)
==11141==    by 0x420942: main (speller.c:40)
==11141== 
==11141== 94,327 bytes in 17,756 blocks are definitely lost in loss record 4 of 6
==11141==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==11141==    by 0x422DCB: check (dictionary.c:108)
==11141==    by 0x421313: main (speller.c:112)
==11141== 
==11141== 1,439,210 bytes in 143,089 blocks are definitely lost in loss record 5 of 6
==11141==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==11141==    by 0x422C2A: trim (dictionary.c:84)
==11141==    by 0x423755: load (dictionary.c:206)
==11141==    by 0x420942: main (speller.c:40)
==11141== 
==11141== 3,977,344 bytes in 17,756 blocks are definitely lost in loss record 6 of 6
==11141==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==11141==    by 0x4222E3: init_node (dictionary.c:22)
==11141==    by 0x422F87: check (dictionary.c:119)
==11141==    by 0x421313: main (speller.c:112)
==11141== 
==11141== LEAK SUMMARY:
==11141==    definitely lost: 5,510,888 bytes in 178,602 blocks
==11141==    indirectly lost: 0 bytes in 0 blocks
==11141==      possibly lost: 0 bytes in 0 blocks
==11141==    still reachable: 578 bytes in 2 blocks
==11141==         suppressed: 0 bytes in 0 blocks
==11141== Reachable blocks (those to which a pointer was found) are not shown.
==11141== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==11141== 
==11141== For counts of detected and suppressed errors, rerun with: -v
==11141== ERROR SUMMARY: 12 errors from 5 contexts (suppressed: 0 from 0)
*/

/*
after fixing another bug

==18228== 
==18228== HEAP SUMMARY:
==18228==     in use at exit: 4,072,246 bytes in 35,514 blocks
==18228==   total heap usage: 545,687 allocs, 510,173 frees, 87,738,402 bytes allocated
==18228== 
==18228== 7 bytes in 1 blocks are definitely lost in loss record 1 of 4
==18228==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==18228==    by 0x422C2A: trim (dictionary.c:84)
==18228==    by 0x423B67: load (dictionary.c:233)
==18228==    by 0x420942: main (speller.c:40)
==18228== 
==18228== 94,327 bytes in 17,756 blocks are definitely lost in loss record 3 of 4
==18228==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==18228==    by 0x422DBB: check (dictionary.c:106)
==18228==    by 0x421313: main (speller.c:112)
==18228== 
==18228== 3,977,344 bytes in 17,756 blocks are definitely lost in loss record 4 of 4
==18228==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==18228==    by 0x4222E3: init_node (dictionary.c:22)
==18228==    by 0x422F77: check (dictionary.c:117)
==18228==    by 0x421313: main (speller.c:112)
==18228== 
==18228== LEAK SUMMARY:
==18228==    definitely lost: 4,071,678 bytes in 35,513 blocks
==18228==    indirectly lost: 0 bytes in 0 blocks
==18228==      possibly lost: 0 bytes in 0 blocks
==18228==    still reachable: 568 bytes in 1 blocks
==18228==         suppressed: 0 bytes in 0 blocks
==18228== Reachable blocks (those to which a pointer was found) are not shown.
==18228== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==18228== 
==18228== For counts of detected and suppressed errors, rerun with: -v
==18228== ERROR SUMMARY: 11 errors from 4 contexts (suppressed: 0 from 0)
*/

/*
after another bug is ousted

==18484== 
==18484== HEAP SUMMARY:
==18484==     in use at exit: 4,072,239 bytes in 35,513 blocks
==18484==   total heap usage: 545,687 allocs, 510,174 frees, 87,738,402 bytes allocated
==18484== 
==18484== 94,327 bytes in 17,756 blocks are definitely lost in loss record 2 of 3
==18484==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==18484==    by 0x422DBB: check (dictionary.c:106)
==18484==    by 0x421313: main (speller.c:112)
==18484== 
==18484== 3,977,344 bytes in 17,756 blocks are definitely lost in loss record 3 of 3
==18484==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==18484==    by 0x4222E3: init_node (dictionary.c:22)
==18484==    by 0x422F77: check (dictionary.c:117)
==18484==    by 0x421313: main (speller.c:112)
==18484== 
==18484== LEAK SUMMARY:
==18484==    definitely lost: 4,071,671 bytes in 35,512 blocks
==18484==    indirectly lost: 0 bytes in 0 blocks
==18484==      possibly lost: 0 bytes in 0 blocks
==18484==    still reachable: 568 bytes in 1 blocks
==18484==         suppressed: 0 bytes in 0 blocks
==18484== Reachable blocks (those to which a pointer was found) are not shown.
==18484== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==18484== 
==18484== For counts of detected and suppressed errors, rerun with: -v
==18484== ERROR SUMMARY: 10 errors from 3 contexts (suppressed: 0 from 0)
*/


/*
==13948== 
==13948== HEAP SUMMARY:
==13948==     in use at exit: 92,474 bytes in 17,540 blocks
==13948==   total heap usage: 527,931 allocs, 510,391 frees, 83,761,058 bytes allocated
==13948== 
==13948== 92,474 bytes in 17,540 blocks are definitely lost in loss record 1 of 1
==13948==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==13948==    by 0x422DBB: check (dictionary.c:106)
==13948==    by 0x421313: main (speller.c:112)
==13948== 
==13948== LEAK SUMMARY:
==13948==    definitely lost: 92,474 bytes in 17,540 blocks
==13948==    indirectly lost: 0 bytes in 0 blocks
==13948==      possibly lost: 0 bytes in 0 blocks
==13948==    still reachable: 0 bytes in 0 blocks
==13948==         suppressed: 0 bytes in 0 blocks
==13948== 
==13948== For counts of detected and suppressed errors, rerun with: -v
==13948== ERROR SUMMARY: 9 errors from 2 contexts (suppressed: 0 from 0)
*/
