#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "JPEG.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file_name \n");
        return 1;
    }

    char *input_file = argv[1];

    FILE *in_filePtr = fopen(input_file,"r");

    if(in_filePtr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", input_file);
        return 2;
    }

    int JPEG_array[51];

    int raw_block_counter = 0;

    int *raw_block_counterPtr = &raw_block_counter;

    int JPEG_counter = 0;

    int *JPEG_counterPtr = &JPEG_counter;

    while (1>0)
    {
        block check;

        fread(&check,sizeof(block),1,in_filePtr);

        if(check.first_bytes == 0xffd8ff)
        {
            JPEG_array[JPEG_counter] = raw_block_counter;

            *JPEG_counterPtr = JPEG_counter+1;
        }

        *raw_block_counterPtr = raw_block_counter+1;

        if(JPEG_counter == 50)
        {
             break;
        }
    }

    fseek(in_filePtr,0,SEEK_END);

    int end_of_file_in_bytes = ftell(in_filePtr);

    int end_of_file = end_of_file_in_bytes/512;

    JPEG_array[JPEG_counter] = end_of_file;

    fseek(in_filePtr, 0, SEEK_SET);

    int i;

    for(i=0; i<50; i++)
    {
        char *output_file_name;

        output_file_name = malloc(10*sizeof(char));

        sprintf(output_file_name, "0%i.jpg", i+1);

        int range = JPEG_array[i+1] - JPEG_array[i];

        char *JPEG = malloc(range*sizeof(block));

        fseek(in_filePtr, JPEG_array[i]*sizeof(block), SEEK_SET);

        fread(JPEG, range*sizeof(block), 1, in_filePtr);

        FILE *out_filePtr;

        out_filePtr = fopen(output_file_name, "w");

        fwrite(JPEG, range*sizeof(block), 1, out_filePtr);

    }
    /*char *output_file_name;

    output_file_name = malloc(10*sizeof(char));

    sprintf(output_file_name, "JPEG%i.JPEG", i+1);

    JPEG_array[i+1] =

    int range = JPEG_array[i+1] - JPEG_array[i];

    char *JPEG = malloc(range*sizeof(block));

    fseek(in_filePtr, JPEG_array[i]*sizeof(block), SEEK_SET);

    fread(JPEG, range*sizeof(block), 1, in_filePtr);

    FILE *out_filePtr;

    out_filePtr = fopen(output_file_name, "w");

    fwrite(JPEG, range*sizeof(block), 1, out_filePtr);*/




}














    //char *output_file = "image20.jpeg";

    //FILE *out_filePtr = fopen(output_file, "w");

    /*for(int i=0; i<1000; i++)
    {

        block dog;

        fread(&dog,sizeof(block),1,in_filePtr);

        if(dog.first_bytes == 0xffd8ff)
        {
            fwrite(&dog, sizeof(block),1,out_filePtr);
            exit(0);
        }
    }*/

    /*nib dog;

    dog.nibble1 = 0xe;

    block cat;

    cat.fourth_byte.nibble1 = 0x0;

    cat.fourth_byte.nibble2 = 0x0;

    printf("%c", cat.fourth_byte.nibble1);*/



