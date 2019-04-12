// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int size;

    char** words;
} Hashtable;

int dict_size;

Hashtable HT;


// Forward Declarations:

unsigned int PJWHash(const char* str, unsigned int length);

char* trim(char word[], int len);

int prime(int ht_size);

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

    int hash_table_size = dict_size * 1.4286;

    int check_index = pre_check_index % hash_table_size;

    Hashtable* HT_Ptr = &HT;

    if(HT_Ptr->words[check_index])
    {

        if(strcmp(HT_Ptr->words[check_index], lowercase_word)==0)
        {
            return true;
        }

        else
        {
            return false;
        }

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
    int hash_table_size = dict_size * 1.4286;

    Hashtable* HT_Ptr = &HT;

    HT_Ptr->size = hash_table_size;

    HT_Ptr->words = calloc(hash_table_size,sizeof(char)*46);

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

            HT_Ptr->words[hash_index] = new_word;

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

    char* new_word = trim(last_word, lw_index-1);

    int pre_hash_index = PJWHash(new_word, lw_index-1);

    int hash_index = pre_hash_index % hash_table_size;

    HT_Ptr->words[hash_index] = new_word;



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
    // TODO
    return true;
}

char* trim(char word[], int len)
{
    char* storage = malloc(sizeof(char)*len);

    for(int i=0; i<=len; i++)
    {
        storage[i] = word[i];

    }

    return storage;


    /*int pre_index = PJWHash(storage, len);

    int index = pre_index % hash_table_size;

    printf("%i%s\n", index, storage);*/

    /*

    printf("%s", storage);*/
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
