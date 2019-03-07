 //Usage: ./search v

// v is the value you want to find

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

// the max for the integers we're using
const int MAX = 65536;

int main(int argc, string argv[])
{
    // directs user for executable input
    if (argc != 2)
    {
        printf("Usage: ./search v\n");
        return -1;
    }

    // define v as a number from command line
    int v = atoi(argv[1]);

    //we use this to fill our array with all the pseudorandom integers once this is meshed with "spawn.c"
    int size;
    int array[MAX];
    for (size = 0; size < MAX; size++)
    {
        //Potential 'End Of File'
        printf("\narray[%i] = ", size);
        int random = get_int();
        //cant be too big
        if (random == INT_MAX)
        {
            break;
        }

        // a
        array[size] = random;
    }
    printf("\n");

    // now we sort the array in order
    order(array, size);

    // now we look for whether the value(v) we are looking for is in the array we "spawned"
    if (search(v, array, size))
    {
        printf("\nFound v!\n\n");
        return 0;
    }
    else
    {
        printf("\nDidn't find v.\n\n");
        return 1;
    }
}
