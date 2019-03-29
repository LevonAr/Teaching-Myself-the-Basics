#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include <math.h>

char *mode(int n, char *pixels[]);

int add_padding(int pointer_for_counter, int total_pixels_original, int padding_bytes);

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize_ratio infile outfile\n");
        return 1;
    }

    double ratio;

    ratio = atof(argv[1]);
    
    //check whether ratio is valid
    if (ratio<= 0.0 || ratio >100.0)
    {
        fprintf(stderr, "ratio is invalid");
        return 2;
    }
    
    // names of files
    char *infile = argv[2];
    char *outfile = argv[3];


    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // if file size is being increased this is the path it will take
    if(ratio>=1)
    {
        int originalPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        double total_pixels = abs(bi.biHeight) * bi.biWidth;

        int newWidth = round(ratio*bi.biWidth);

        int newHeight = round(ratio*bi.biHeight);

        int originalWidth = bi.biWidth;

        int originalHeight = abs(bi.biHeight);

        double per_pixel_ratio_A = (newWidth*newWidth)/total_pixels;

        double per_pixel_ratio = fabs(per_pixel_ratio_A);

        double base_pixel_ratio = sqrt(per_pixel_ratio);

        bi.biWidth = newWidth;

        bi.biHeight = newHeight;

        int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        bi.biSizeImage =  (bi.biWidth * sizeof(RGBTRIPLE) + newPadding)* abs(bi.biHeight);

        bf.bfSize = bi.biSizeImage +54;

        // write outfile's BITMAPFILEHEADER
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

        // write outfile's BITMAPINFOHEADER
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

        bi.biWidth = originalWidth;

        bi.biHeight = originalHeight;


        // iterates over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            int per_pixel_height = round((i+1)*base_pixel_ratio) - round(i*base_pixel_ratio);

            for(int m=0; m<per_pixel_height;m++)
            {
            // iterate's over pixels in scanline
                for (int j = 0; j < bi.biWidth; j++)
                {
                    // temporary storage for a pixel
                    RGBTRIPLE triple;

                    // read RGB triple(each pixel) from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    int per_pixel_width = round((j+1)*base_pixel_ratio) - round(j*base_pixel_ratio);

                    for(int n=0;n<per_pixel_width;n++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }

                for (int k = 0; k < newPadding; k++)
                    {
                        fputc(0x00, outptr);
                    }

                int back_it_up = (bi.biWidth*sizeof(RGBTRIPLE))*-1;

                int tapper = per_pixel_height - 1;

                if(m!=tapper)
                {
                    fseek(inptr, back_it_up, SEEK_CUR);
                }
            }
            // skip over padding, if any
            fseek(inptr, originalPadding, SEEK_CUR);
        }

        // close infile
        fclose(inptr);

        // close outfile
        fclose(outptr);

        // success
        return 0;
    }

    if(ratio<1)
    {
        int originalPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        double total_pixels = abs(bi.biHeight) * bi.biWidth;

        int newWidth = round(ratio*bi.biWidth);

        int newHeight = round(ratio*bi.biHeight);

        int originalWidth = bi.biWidth;

        int originalHeight = abs(bi.biHeight);

        double per_pixel_ratio_A = total_pixels/(newWidth*newWidth);

        double per_pixel_ratio = fabs(per_pixel_ratio_A);

        double width_pixel_ratio = sqrt(per_pixel_ratio);

        bi.biWidth = newWidth;

        bi.biHeight = newHeight;

        int pixel_counter = 54;

        int *pixel_counter_Ptr = &pixel_counter;

        int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        bi.biSizeImage =  (bi.biWidth * sizeof(RGBTRIPLE) + newPadding)* abs(bi.biHeight);

        bf.bfSize = bi.biSizeImage +54;

        //int interval_counter = 0;

        //int *interval_counter_Ptr = &interval_counter;

        // write outfile's BITMAPFILEHEADER
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

        // write outfile's BITMAPINFOHEADER
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            int per_pixel_height = round((i+1)*width_pixel_ratio) - round(i*width_pixel_ratio);

            // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth; j++)
                {
                    // temporary storage
                    int interval_counter = 0;

                    int per_pixel_width = round((j+1)*width_pixel_ratio) - round(j*width_pixel_ratio);

                    int x = per_pixel_height*per_pixel_width;

                    char *old_triple[x];

                    for(int p=0;p<x;p++)
                    {
                        old_triple[p] = malloc(sizeof(RGBTRIPLE));
                    }


                    for(int q=0; q<x;q++)
                    {

                        fread(old_triple[q], sizeof(RGBTRIPLE), 1, inptr);

                        interval_counter = interval_counter+1;

                        //int whole_number_checker = (int)interval_counter;

                        if(interval_counter % per_pixel_width == 0)
                        {
                            if(interval_counter % (per_pixel_height*per_pixel_width) == 0)
                            {
                                int last_row = (originalWidth*3)-(per_pixel_width*3);

                                int base_rows = (originalWidth*3)*(per_pixel_height-2);

                                int back_it_up = base_rows + last_row;

                                *pixel_counter_Ptr = pixel_counter-back_it_up;

                                int addPad = add_padding(pixel_counter, total_pixels, originalPadding);

                                int seek_offset = pixel_counter + addPad;

                                fseek(inptr,seek_offset,SEEK_SET);
                            }


                            else
                            {
                                *pixel_counter_Ptr = pixel_counter+(originalWidth*3);

                                int addPad = add_padding(pixel_counter, total_pixels, originalPadding);

                                int seek_offset = pixel_counter + addPad;

                                fseek(inptr,seek_offset,SEEK_SET);
                            }
                        }
                    }

                    char *new_triple = mode(x, old_triple);

                    fwrite(new_triple, sizeof(RGBTRIPLE), 1, outptr);

                    //printf("%p\n", new_triple);

                }

                *pixel_counter_Ptr = pixel_counter+(per_pixel_height-1)*(originalWidth*3);

                 for (int k = 0; k < newPadding; k++)
                    {
                        fputc(0x00, outptr);
                    }

                int addPad = add_padding(pixel_counter, total_pixels, originalPadding);

                int seek_offset = pixel_counter + addPad;

                fseek(inptr,seek_offset,SEEK_SET);


        }

        // close infile
        fclose(inptr);

        // close outfile
        fclose(outptr);

        // success
        return 0;
    }
}

char* mode(int n, char *pixels[])
{
   char *maxValue;
   int maxCount = 0;
   int i;
   int j;

   for (i = 0; i < n; ++i) {
      int count = 0;

      for (j = 0; j < n; ++j) {
         if (strcmp (pixels[j], pixels[i]) == 0)
         ++count;
      }

      if (count > maxCount) {
         maxCount = count;
         maxValue = pixels[i];
      }
   }

   return maxValue;
}

int add_padding(int pointer_for_counter, int total_pixels_original, int padding_bytes)
{
    int base_interval = sqrt(total_pixels_original)*3;

    int padding_added = ((pointer_for_counter-54)/base_interval)*padding_bytes;

    return padding_added;
}
