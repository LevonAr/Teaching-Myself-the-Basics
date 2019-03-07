**#Order_Search**

I designed Order_Search to be able to take a collection of integers, sort them in ascending order, then identify whether a certain value was among this particular set of numbers. I decided to use a comparison-based sorting algorithm called merge sort to arrange this group of numbers in order. I then choose to use a search algorithm called binary search to look for the value.
My main goal with writing this program was to deepen my understanding of recursion. I used recursion while writing the code for my binary search and merge sort, both of which are set in the file utility.c

##spawn.c

This program was designed to provide me with an 'n' amount of pseudorandom integers to work with. The usage of this file is as follows:

##spawn n [s]
Where n is the number of integers we want "spawned", and s is an optional seed. 
Without the seed, the program generates a new set of pseudorandom integers every time you use it. However, the seed allows for the same set of pseudorandom integers to be replicated. For instance, the command:  ./spawn 40 [2] will generate the same set of 40 numbers every time it is used. 
This option will help us check whether our searching function works because we can know for sure whether a certain number is in the list.  
##search.c 

Meshes all the numbers created in spawn.c with the main functions of this program that arrange them in order and comb through them looking for a specific value 

##utility.c

These are the real guts of this program. The two main mechanism at play are 'search' and 'order'.

######order
order's purpose is to arrange the set of pseudorandom integers in ascending order. This is done using a merge sort algorithm.
 
######search
search's purpose is to find whether or not a specific value exist in our pseudorandomly generated. As such it has a boolean return type because its either true or false. First the number are arranged in order using 'order'. Then we use a binary search by implementing recursion. 
