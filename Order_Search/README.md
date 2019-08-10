# Order Search

## Getting Started

### Prerequisites 

#### Get Compiler

This program is written in C, so you must compile it before you can run it.

In order to do this, you need a compiler. If you don't have one or don't know if you do, complete the following steps to install GCC:

#### For PC

##### Using Visual Studio Code (Recommended):

1. Open the '/Rescale' folder.

2. Install the C/C++ extension so we can compile the program.


##### Using Command Prompt:

1. Open Command Prompt and type
```
gcc -v
```
If gcc is installed then it should display a host of information starting with the sentence “Using built-in specs”

2. If you don't have gcc and are determined to run this in your Command Prompt, go to [this](https://preshing.com/20141108/how-to-install-the-latest-gcc-on-windows/ "Install GCC") link and follow the instructions to install gcc. However, the easier route would be to just use VScode.

#### For Mac:

Follow the installation instructions to [here](https://www.mkyong.com/mac/how-to-install-gcc-compiler-on-mac-os-x/ "Install GCC") to install GCC on your terminal.





# BEHIND THE SCENES

I designed Order_Search to be able to take a collection of integers, sort them in ascending order, then identify whether a certain value was among this particular set of numbers. I decided to use a comparison-based sorting algorithm called merge sort to arrange this group of numbers in order. I then choose to use a search algorithm called binary search to look for the value.
My main goal with writing this program was to deepen my understanding of recursion. I used recursion while writing the code for my binary search and merge sort, both of which are set in the file utility.c

## spawn.c

This program was designed to provide me with an 'n' amount of pseudorandom integers to work with. The usage of this file is as follows:

**spawn n [s]**

Where n is the number of integers we want "spawned", and s is an optional seed. 
Without the seed, the program generates a new set of pseudorandom integers every time you use it. However, the seed allows for the same set of pseudorandom integers to be replicated. For instance, the command:  ./spawn 40 [2] will generate the same set of 40 numbers every time it is used. 
This option will help us check whether our searching function works because we can know for sure whether a certain number is in the list.  
## search.c 

Meshes all the numbers created in spawn.c with the main functions of this program that arrange them in order and comb through them looking for a specific value 

## utility.c

These are the real guts of this program. The two main mechanism at play are 'search' and 'order'.

### order
order's purpose is to arrange the set of pseudorandom integers in ascending order. This is done using a merge sort algorithm.
 
### search
search's purpose is to find whether or not a specific value exist in our pseudorandomly generated. As such it has a boolean return type because its either true or false. First the number are arranged in order using 'order'. Then we use a binary search by implementing recursion. 
