//Usage: spawn n [s]

//n is number of pseudorandom numbers you want and s is an optional seed

#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// max number for integers
#define LIMIT 65536

int main(int argc, string argv[])
{
    // directs user for executable input
    if (argc != 2 && argc != 3)
    {
        printf("Usage:  ./spawn n [s]\n");
        return 1;
    }

    // defines 'n' as a number
    int n = atoi(argv[1]);

    // checks whether optional seed is used
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    // prints out all the pseudorandom numbers
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    return 0;
}
