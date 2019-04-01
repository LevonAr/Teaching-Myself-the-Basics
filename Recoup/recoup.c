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

    int JPEG_counter = 0;

    int *JPEG_counterPtr = &JPEG_counter;

    while (1>0)
    {
        block check;

        fread(&check,sizeof(block),1,in_filePtr);

        if(check.first_bytes == 0xffd8ff)
        {
            JPEG_array[JPEG_counter] = raw_block_counter;

            JPEG_counter++;
        }

        raw_block_counter++;

        if(JPEG_counter == 50)
        {
            break;
        }
    }

    while(1<0)
    {
        block last_JPEG_check;

        fread(&last_JPEG_check, sizeof(block), 1, in_filePtr);

        if( last_JPEG_check.first_bytes == 0x000000)
        {
            JPEG_array[JPEG_counter] = last_JPEG_counter;

            break;
        }

        last_JPEG_counter ++;
    }

    /*for(int i=0; i<50; i++)
    {
        printf("%i\n", JPEG_array[i]);
    }*/

    fseek(in_filePtr, 0, SEEK_SET);

    int i;

    for(i=0; i<50; i++)
    {
        char *output_file_name;

        output_file_name = malloc(10*sizeof(char));

        sprintf(output_file_name, "JPEG%i.jpg", i+1);

        int range = JPEG_array[i+1] - JPEG_array[i];

        char *JPEG = malloc(range*sizeof(block));

        fseek(in_filePtr, JPEG_array[i]*sizeof(block), SEEK_SET);

        fread(JPEG, range*sizeof(block), 1, in_filePtr);

        FILE *out_filePtr;

        out_filePtr = fopen(output_file_name, "w");

        fwrite(JPEG, range*sizeof(block), 1, out_filePtr);

    }

    int last_JPEG_counter = 0;

    while(1<0)
    {
        block last_JPEG_check;

        fread(&last_JPEG_check, sizeof(block), 1, in_filePtr);

        if( last_JPEG_check.first_bytes == 0x000000)
        {
            JPEG_array[i] = last_JPEG_counter;

            break;
        }

        last_JPEG_counter ++;
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
