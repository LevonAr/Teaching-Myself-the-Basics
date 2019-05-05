/*Times

WORDS MISSPELLED:     955
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        17756
TIME IN load:         0.10
TIME IN check:        0.02
TIME IN size:         0.00
TIME IN unload:       0.02
TIME IN TOTAL:        0.13

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

        /*if(strcmp(HT_Ptr->words[check_index]->word, lowercase_word)==0)
        {
            return true;
        }

        else
        {
            return false;
        }*/

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


/*
memcheck report

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
==2987== ERROR SUMMARY: 5 errors from 5 contexts (suppressed: 0 from 0)*/

/*
==4622== 
==4622== HEAP SUMMARY:
==4622==     in use at exit: 3,816,514 bytes in 201,300 blocks
==4622==   total heap usage: 303,942 allocs, 102,642 frees, 5,459,338 bytes allocated
==4622== 
==4622== 7 bytes in 1 blocks are definitely lost in loss record 1 of 9
==4622==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==4622==    by 0x424D9A: trim (dictionary.c:254)
==4622==    by 0x423FE3: load (dictionary.c:216)
==4622==    by 0x420982: main (speller.c:40)
==4622== 
==4622== 94,327 bytes in 17,756 blocks are definitely lost in loss record 4 of 9
==4622==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==4622==    by 0x42235E: check (dictionary.c:52)
==4622==    by 0x421353: main (speller.c:112)
==4622== 
==4622== 1,033,040 bytes in 102,640 blocks are definitely lost in loss record 7 of 9
==4622==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==4622==    by 0x424D9A: trim (dictionary.c:254)
==4622==    by 0x423717: load (dictionary.c:171)
==4622==    by 0x420982: main (speller.c:40)
==4622== 
==4622== 1,053,380 (508,240 direct, 545,140 indirect) bytes in 31,765 blocks are definitely lost in loss record 8 of 9
==4622==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==4622==    by 0x4255A3: makeLink (dictionary.c:348)
==4622==    by 0x424EF7: addLink (dictionary.c:361)
==4622==    by 0x423A76: load (dictionary.c:189)
==4622==    by 0x420982: main (speller.c:40)
==4622== 
==4622== LEAK SUMMARY:
==4622==    definitely lost: 1,635,614 bytes in 152,162 blocks
==4622==    indirectly lost: 545,140 bytes in 49,135 blocks
==4622==      possibly lost: 0 bytes in 0 blocks
==4622==    still reachable: 1,635,760 bytes in 3 blocks
==4622==         suppressed: 0 bytes in 0 blocks
==4622== Reachable blocks (those to which a pointer was found) are not shown.
==4622== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==4622== 
==4622== For counts of detected and suppressed errors, rerun with: -v
==4622== ERROR SUMMARY: 5 errors from 5 contexts (suppressed: 0 from 0)
*/
