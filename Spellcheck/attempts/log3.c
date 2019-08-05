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

//Perfected trie 

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
    freedom(base_root);

    return true;
}



/*

my perfected trie memcheck report
==2623== 
==2623== HEAP SUMMARY:
==2623==     in use at exit: 0 bytes in 0 blocks
==2623==   total heap usage: 527,931 allocs, 527,931 frees, 83,761,059 bytes allocated
==2623== 
==2623== All heap blocks were freed -- no leaks are possible
==2623== 
==2623== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==2623== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>


typedef struct _node
{
    char* word;

    struct _node *next;
} node ;

typedef struct
{
    int size;

    node **words;
} Hashtable;


int dict_size;

Hashtable* HT_Ptr;

//just checking if my linked list works
int linked_list_counter;

int hash_table_size;


// Forward Declarations:

unsigned int PJWHash(const char* str, unsigned int length);

char* trim(char word[], int len);

int prime(int ht_size);

node* makeLink(void);

node* addLink(node* link, char* add_word);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //turn all words into lowercase because directions specify check to be case insensitive and all words in dictionary are required to be lowercase
    char* lowercase_word = malloc((strlen(word)+1)*sizeof(char)) ;

    int i;

    for(i=0; i<strlen(word); i++)
    {
        lowercase_word[i] = tolower(word[i]);
    }

    lowercase_word[i]= '\0';

    int pre_check_index = PJWHash(lowercase_word,strlen(word));

    int check_index = pre_check_index % hash_table_size;

    if(HT_Ptr->words[check_index])
    {
        if(strcmp(HT_Ptr->words[check_index]->word, lowercase_word)==0)
        {
            return true;
        }

        bool check_bucket = false;


        for(node* Ptr = HT_Ptr->words[check_index]; Ptr->next != NULL; Ptr = Ptr->next)
            {
                if(strcmp(Ptr->next->word, lowercase_word)==0)
                {
                    check_bucket = true;
                    int* LLP = &linked_list_counter;
                    *LLP = linked_list_counter + 1;
                    break;
                }

            }

            return check_bucket;
    }

    else
    {
        return false;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *load_file = fopen(dictionary, "r");

    if(!load_file)
    {
        printf("%s", "could not open dictionary");

        return 1;
    }

    //lets figure out the fastes way to store each word in the least of memory

    // make it more accessible  ?maybe a trie? for check later on so our times are good

    int new_line_counter = 1;

    for (int c = fgetc(load_file); c != EOF; c = fgetc(load_file))
    {
        if( c== '\n')
        {
            new_line_counter++;
        }

    }

    int *dict_size_Ptr = &dict_size;

    *dict_size_Ptr = new_line_counter;

    // according to the LOAD FACTOR the amount of 'buckets' that are should only be around 70% of the size of the hash table, hence i multiply be inverse of .7
    int *hash_table_size_Ptr = &hash_table_size;

    *hash_table_size_Ptr = prime (dict_size * 1.4286);

    HT_Ptr = malloc(sizeof(Hashtable));

    HT_Ptr->size = hash_table_size;

    HT_Ptr->words = calloc(hash_table_size,sizeof(node*));

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

            int pre_hash_index = PJWHash(new_word, index);

            int hash_index = pre_hash_index % hash_table_size;

            node* temp = NULL;

            if(!HT_Ptr->words[hash_index])
            {
                temp = NULL;
            }

            else
            {
                temp = HT_Ptr->words[hash_index];
            }

            node* word_node = addLink(temp, new_word);

            HT_Ptr->words[hash_index] = word_node;

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

    int pre_hash_index = PJWHash(last__word, lw_index-1);

    int hash_index = pre_hash_index % hash_table_size;

    node* last_word_in = NULL;

    node* last_word_node = addLink(last_word_in, last__word);

    HT_Ptr->words[hash_index] = last_word_node;


    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i=0; i<=hash_table_size; i++)
    {
        if(HT_Ptr->words[i])
        {
            free(HT_Ptr->words[i]);
        }
    }

    return true;
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


// hash function by Peter J. Weinberger
unsigned int PJWHash(const char* str, unsigned int length)
{
   const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   const unsigned int HighBits          =
                      (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash = 0;
   unsigned int test = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << OneEighth) + (*str);

      if ((test = hash & HighBits) != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}

int prime(int ht_size)
{


    int i;
    int j;
    int numbers[ht_size];

    /*fill the array with natural numbers*/
    for (i=0;i<ht_size;i++)
    {
        numbers[i]=i+2;
    }

    int prime_counter = ht_size;

    /*sieve the non-primes*/
    for (i=0; i<ht_size; i++)
    {
        if (numbers[i]!=-1)
        {
            for (j=2*numbers[i]-2; j<ht_size; j+=numbers[i])
            {
                numbers[j]=-1;
            }
        }

        else
        {
           prime_counter = prime_counter -1;
        }
    }

    int primes[prime_counter];

    /*transfer the primes to their own array*/

    j = 0;

    for (i=0; i<ht_size&&j<prime_counter; i++)
    {
       if (numbers[i]!=-1)
       {
          primes[j++] = numbers[i];
       }

    }



    return primes[prime_counter-1];
}

node* makeLink(void)
{
    node* temp;

    temp = malloc(sizeof(node));

    temp->next = NULL;

    return temp;
}

node* addLink(node* link, char* add_word)
{
    node* temp = NULL;

    node* ptr = NULL;

    temp = makeLink();

    temp->word = add_word;

    if (link == NULL)
    {
        temp->next = NULL;

        link = temp;

    }

    else
    {
        ptr = link;

        while(ptr->next != NULL)
        {
            ptr = ptr->next;
        }

        ptr->next = temp;
    }

    return link;
}


// memcheck report
/*
--2987-- REDIR: 0x5a00120 (libc.so.6:free) redirected to 0x4c2bd80 (free)
==2987== Invalid read of size 8
==2987==    at 0x425408: unload (dictionary.c:243)
==2987==    by 0x421554: main (speller.c:152)
==2987==  Address 0x5ed5678 is 0 bytes after a block of size 1,635,176 alloc'd
==2987==    at 0x4C2CC70: calloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==2987==    by 0x4234F8: load (dictionary.c:149)
==2987==    by 0x420982: main (speller.c:40)
==2987== 

WORDS MISSPELLED:     955
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        17756
TIME IN load:         3.50
TIME IN check:        0.28
TIME IN size:         0.00
TIME IN unload:       0.28
TIME IN TOTAL:        4.07

==2987== 
==2987== HEAP SUMMARY:
==2987==     in use at exit: 3,816,514 bytes in 201,300 blocks
==2987==   total heap usage: 303,942 allocs, 102,642 frees, 5,459,338 bytes allocated
==2987== 
==2987== Searching for pointers to 201,300 not-freed blocks
==2987== Checked 12,621,808 bytes
==2987== 
==2987== 7 bytes in 1 blocks are definitely lost in loss record 1 of 9
==2987==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==2987==    by 0x424D9A: trim (dictionary.c:254)
==2987==    by 0x423FE3: load (dictionary.c:216)
==2987==    by 0x420982: main (speller.c:40)
==2987== 
==2987== 94,327 bytes in 17,756 blocks are definitely lost in loss record 4 of 9
==2987==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==2987==    by 0x42235E: check (dictionary.c:52)
==2987==    by 0x421353: main (speller.c:112)
==2987== 
==2987== 1,033,040 bytes in 102,640 blocks are definitely lost in loss record 7 of 9
==2987==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==2987==    by 0x424D9A: trim (dictionary.c:254)
==2987==    by 0x423717: load (dictionary.c:171)
==2987==    by 0x420982: main (speller.c:40)
==2987== 
==2987== 1,053,380 (508,240 direct, 545,140 indirect) bytes in 31,765 blocks are definitely lost in loss record 8 of 9
==2987==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==2987==    by 0x4255A3: makeLink (dictionary.c:348)
==2987==    by 0x424EF7: addLink (dictionary.c:361)
==2987==    by 0x423A76: load (dictionary.c:189)
==2987==    by 0x420982: main (speller.c:40)
==2987== 
==2987== LEAK SUMMARY:
==2987==    definitely lost: 1,635,614 bytes in 152,162 blocks
==2987==    indirectly lost: 545,140 bytes in 49,135 blocks
==2987==      possibly lost: 0 bytes in 0 blocks
==2987==    still reachable: 1,635,760 bytes in 3 blocks
==2987==         suppressed: 0 bytes in 0 blocks
==2987== Reachable blocks (those to which a pointer was found) are not shown.
==2987== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==2987== 
==2987== ERROR SUMMARY: 5 errors from 5 contexts (suppressed: 0 from 0)
==2987== 
==2987== 1 errors in context 1 of 5:
==2987== Invalid read of size 8
==2987==    at 0x425408: unload (dictionary.c:243)
==2987==    by 0x421554: main (speller.c:152)
==2987==  Address 0x5ed5678 is 0 bytes after a block of size 1,635,176 alloc'd
==2987==    at 0x4C2CC70: calloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==2987==    by 0x4234F8: load (dictionary.c:149)
==2987==    by 0x420982: main (speller.c:40)
==2987== 
==2987== ERROR SUMMARY: 5 errors from 5 contexts (suppressed: 0 from 0)
*/

