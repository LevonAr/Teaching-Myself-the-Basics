// Implements a dictionary's functionality

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

        bool check_bucket = false;

        if(strcmp(HT_Ptr->words[check_index]->word, lowercase_word)==0)
        {
            return true;
        }

        else
        {
            for(node* Ptr = HT_Ptr->words[check_index]; Ptr->next != NULL; Ptr = Ptr->next)
            {                                               XXXXXXXXXXX
                                                            XXXXXXXXXXX
                //if(strcmp(Ptr->word, lowercase_word)==0)  XXXXBUGXXXX
                                                            XXXXXXXXXXX
                                                            XXXXXXXXXXX
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

    //HT_Ptr->size = hash_table_size;

    HT_Ptr = malloc(sizeof(Hashtable));                 XXXXXXXXXXX     // apparently this program works even with this bug. Need to come back to this later and find out why.
                                                        XXXXXXXXXXX
    HT_Ptr->words = calloc(hash_table_size,sizeof(node  XXXXBUGXXXX  )); // took me around 8 hours of debugging.
                                                        XXXXXXXXXXX      // I literally drew around 10  pages of diagrams of pointers.
    fseek(load_file, 0, SEEK_SET);                      XXXXXXXXXXX      // The problem is i used calloc with node instead of node*. This ended up being a unique bug because the first part of the struct node is a char*, so im assuming the computer just followed the pointer to the word and stored that, which is not too far off from what is supposed to happen, so the program saved most of the words correctly. But obviously this is completely wrong, so it only correctly stored about 70% of the words. Im assuming the second buckets are where most of the damage happened.

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
