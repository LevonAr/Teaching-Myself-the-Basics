#include <cs50.h>
#include "utility.h"

// most of the actual work I did was here

// forward declaring "sort" and "binary_search" which I define more in depth later
void order(int values[], int n);

bool binary_search(int value, int values[], int n, int lowest_place, int highest_place);


// checks whether the number you are searching for (value) is in the array of pseudorandom numbers we created(values) in spawn.c
bool search(int value, int values[], int n)
{
    //calls "order" which organizes all the pseudorandom numbers in ascending order, making a binary search possible
    order(values, n);

    int binary = binary_search(value, values, n, 0, n-1);

    return binary;
}

// I wanted to get a better grasp on recursion so I played around with it here.

// if this function returns (0)-the number was found.   if it returns (1)-the number was not found.
bool binary_search(int value, int values[], int n, int lowest_place, int highest_place)
{
    // This will be the variable we return. Here I am just declaring it
    int binary=0;

    // The flow of this function will keep dividing n unless the number is found. By the time n=0, all the places the number could possibly be are exhausted
    // thus we return 0 indicating the number wasn't found.
    if (n==0)
    {
        return 0;
    }

    n = n/2;

    int midpoint= (lowest_place+highest_place)/2;

    // We check if the number in the middle of the range we are checking is our "value". If not we either check the range above it or below it. Then using
    // recursion we repeat this logic.
    if(value == values[midpoint])
    {
        return 1;
    }

    else if(value < values[midpoint])
    {
        binary=binary_search(value, values, n, lowest_place, midpoint);
    }

    else if(value > values[midpoint])
    {
        binary=binary_search(value, values, n, midpoint+1, highest_place);

    }

    return binary;

}



//forward declarations
int merge_sort(int values[], int lowest_place, int highest_place, int n);

int combine (int values[], int lowest, int middle, int highest, int n);


// Again I wanted to play around with recursion so I used it here.
// This function orders the array of pseudorandom "values" in ascending order.
void order(int values[], int n)

// converting n into a range which will be useful for recursion
{
    int lowest__place = 0;
    int highest__place = n-1;

    merge_sort(values, lowest__place, highest__place, n);
}


// Writing this was what I would call a "tough cookie" for me at this point in my C journey. There's a lot going on so I wont comment on everything,
// it's just the merge sort logic written in C. Suffice it to say I went over this concept so many times it's burned in my brain.

// Here, I implement the comparison based sorting algorithm known as merge sort
int merge_sort(int values[], int lowest_place, int highest_place, int n)
{
    if(lowest_place < highest_place)
    {
        // decides which section of our range to focus on
        int middle_place;
        middle_place = (highest_place+lowest_place)/2;

        //yay recursion!!
        merge_sort(values, lowest_place, middle_place, n);

        merge_sort(values, middle_place+1, highest_place, n);

        combine(values, lowest_place, middle_place, highest_place, n);

    }

    return 0;

}

//compares the values in the range given and orders them
int combine (int values[], int lowest, int middle, int highest, int n)
{
    // create two temporary arrays in order to compare values
    int left_array[n];
    int right_array[n];

    int max_left= middle-lowest+1;
    int max_right= highest-middle;

    // define the initial variables used in our for loops more globally. This is VITAL.
    int i;
    int j;
    int k;

    //fill temporary arrays
    for(i=0; i<max_left; i++)
    {
        left_array[i]=values[lowest+i];
    }

    // define last [i] value as a really large number to have something to compare to when the two temporary arrays are of a different length. (Off by 1)
    left_array[i]=65536;

    for(j=0; j<max_right; j++)
    {
        right_array[j]=values[middle+j+1];
    }

    right_array[j]=65536;

    // reset i,j in order to properly compare our two temporary arrays
    i=0;
    j=0;

    // compare two temporary arrays and store the result in our original "values"
    for(k=lowest; k<=highest;k++)
    {
        if(left_array[i]<=right_array[j])
        {
            values[k]= left_array[i];
            i++;
        }
        else
        {
            values[k]= right_array[j];
            j++;
        }
    }

    return 0;
}
