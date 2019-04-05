#include <stdio.h>
#include <stdint.h>
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

    // set input file pointer to the file name written by user
    char *input_file = argv[1];

    FILE *in_filePtr = fopen(input_file,"r");

    if(in_filePtr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", input_file);
        return 2;
    }
    
    // Run through the raw file data to check how many JPEGs there are.
    // This is done by checking for the JPEG signature which is the first three and a half bytes being 0xffd8ffe

    bloc end;

    int array_size_counter = 0;

    int *array_size_counterPtr = &array_size_counter;

    while (feof(in_filePtr) == 0)
    {
        bloc check;

        fread(&check,sizeof(bloc),1,in_filePtr);

        if(check.first_bytes == 0xffd8ff)
        {
            *array_size_counterPtr = array_size_counter+1;
        }

    }


    int JPEG_array[array_size_counter+1];

    int raw_block_counter = 0;

    int *raw_block_counterPtr = &raw_block_counter;

    int JPEG_counter = 0;

    int *JPEG_counterPtr = &JPEG_counter;

    fseek(in_filePtr, 0, SEEK_SET);

    while (1>0)
    {
        bloc check;

        fread(&check,sizeof(bloc),1,in_filePtr);

        if(check.first_bytes == 0xffd8ff)
        {
            JPEG_array[JPEG_counter] = raw_block_counter;

            *JPEG_counterPtr = JPEG_counter+1;
        }

        *raw_block_counterPtr = raw_block_counter+1;

        if(JPEG_counter == array_size_counter)
        {
             break;
        }
    }

    fseek(in_filePtr,0,SEEK_END);

    int end_of_file_in_bytes = ftell(in_filePtr);

    int last_block = end_of_file_in_bytes/512;

    JPEG_array[JPEG_counter] = last_block;

    fseek(in_filePtr, 0, SEEK_SET);

    int i;

    for(i=0; i<array_size_counter; i++)
    {
        char *output_file_name;

        output_file_name = malloc(10*sizeof(char));

        sprintf(output_file_name, "%03d.jpg", i);

        int range = JPEG_array[i+1] - JPEG_array[i];

        char *JPEG = malloc(range*sizeof(bloc));

        fseek(in_filePtr, JPEG_array[i]*sizeof(bloc), SEEK_SET);

        fread(JPEG, range*sizeof(bloc), 1, in_filePtr);

        FILE *out_filePtr = fopen(output_file_name, "w");

        fwrite(JPEG, range*sizeof(bloc), 1, out_filePtr);

        fclose(out_filePtr);

    }

    fclose(in_filePtr);

    return 0;
}


